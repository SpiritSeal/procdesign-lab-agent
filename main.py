#!/usr/bin/env python3
"""
Lab Agent - Completes CS3220 Lab #2 (Branch Prediction) using Google Generative AI.

Pipeline:
  Stage 1 (planning probe): Give the model tree + README; it lists files it needs.
  Stage 2 (planning):       Give the model the file contents; it writes a plan.
  Stage 3 (execution loop): The model iteratively edits files, runs tests, and submits.

Environment variables:
  GOOGLE_API_KEY  – required
  MODEL_PLAN      – model for stages 1+2  (default: gemini-3.1-pro-preview)
  MODEL_LOOP      – model for stage 3 loop (default: gemini-3-flash-preview)
  MODEL           – overrides both MODEL_PLAN and MODEL_LOOP if set
  EDIT_MODE       – "full" (default) or "diff"
  ASSIGNMENT_DIR  – path to the assignment directory (default: /app/assignment)
  OUTPUT_DIR      – directory for log, cost report, and final files (default: /output)
  MAX_ITERATIONS  – stage-3 iteration cap (default: 60)
"""

import json
import os
import re
import shutil
import subprocess
import logging
from dataclasses import dataclass, field

from google import genai
from google.genai import types

# ---------------------------------------------------------------------------
# Configuration
# ---------------------------------------------------------------------------
GOOGLE_API_KEY = os.environ.get("GOOGLE_API_KEY", "")

_model_override = os.environ.get("MODEL", "")
MODEL_PLAN = _model_override or os.environ.get("MODEL_PLAN", "gemini-3.1-pro-preview")
MODEL_LOOP = _model_override or os.environ.get("MODEL_LOOP", "gemini-3-flash-preview")

EDIT_MODE      = os.environ.get("EDIT_MODE", "full")   # "full" | "diff"
ASSIGNMENT_DIR = os.environ.get("ASSIGNMENT_DIR", "/app/assignment")
MAX_ITERATIONS = int(os.environ.get("MAX_ITERATIONS", "60"))

_ts        = __import__("datetime").datetime.now().strftime("%Y%m%d_%H%M%S")
OUTPUT_DIR = os.environ.get("OUTPUT_DIR", f"/output")
LOG_FILE   = os.path.join(OUTPUT_DIR, "agent.log")

# Language fence names the model might mistakenly use instead of ```edit
LANG_FENCES = {
    'verilog', 'v', 'sv', 'systemverilog', 'c', 'cpp', 'c++', 'cxx',
    'python', 'py', 'bash', 'sh', 'shell', 'js', 'javascript',
    'ts', 'typescript', 'json', 'yaml', 'toml', 'text', 'txt', 'plaintext',
}

# Regex to find all SEARCH/REPLACE blocks inside a diff-mode edit body
_DIFF_BLOCK_RE = re.compile(
    r"<<<<<<< SEARCH\n(.*?)\n=======\n(.*?)\n>>>>>>> REPLACE",
    re.DOTALL,
)


# ---------------------------------------------------------------------------
# Cost tracking
# ---------------------------------------------------------------------------

# USD per 1M tokens: (input, output).
# Preview model prices are estimates – update when Google publishes official rates.
MODEL_PRICES: dict[str, tuple[float, float]] = {
    "gemini-3.1-pro-preview":  (1.25,  5.00),
    "gemini-3-flash-preview":  (0.075, 0.30),
    "gemini-2.5-pro-preview":  (1.25,  10.00),
    "gemini-2.0-pro-exp":      (0.0,   0.0),   # free during experiment
    "gemini-2.0-flash":        (0.075, 0.30),
    "gemini-2.0-flash-lite":   (0.019, 0.075),
    "gemini-1.5-pro":          (1.25,  5.00),
    "gemini-1.5-flash":        (0.075, 0.30),
}
_FALLBACK_PRICE = (1.00, 4.00)  # used for any model not in the table


@dataclass
class _CallRecord:
    model:        str
    stage:        str
    input_tok:    int
    output_tok:   int
    input_cost:   float
    output_cost:  float

    @property
    def total_cost(self) -> float:
        return self.input_cost + self.output_cost


class CostTracker:
    def __init__(self):
        self._calls: list[_CallRecord] = []

    def record(self, model: str, stage: str, input_tok: int, output_tok: int) -> None:
        in_p, out_p = MODEL_PRICES.get(model, _FALLBACK_PRICE)
        self._calls.append(_CallRecord(
            model=model, stage=stage,
            input_tok=input_tok, output_tok=output_tok,
            input_cost=input_tok * in_p / 1_000_000,
            output_cost=output_tok * out_p / 1_000_000,
        ))

    @property
    def total_cost(self) -> float:
        return sum(c.total_cost for c in self._calls)

    @property
    def total_input_tokens(self) -> int:
        return sum(c.input_tok for c in self._calls)

    @property
    def total_output_tokens(self) -> int:
        return sum(c.output_tok for c in self._calls)

    def log_summary(self, logger: logging.Logger) -> None:
        logger.info("============================================================")
        logger.info("Cost Summary")
        logger.info("============================================================")

        # Aggregate by model
        agg: dict[str, dict] = {}
        for c in self._calls:
            if c.model not in agg:
                agg[c.model] = {"calls": 0, "input_tok": 0, "output_tok": 0, "cost": 0.0}
            agg[c.model]["calls"]      += 1
            agg[c.model]["input_tok"]  += c.input_tok
            agg[c.model]["output_tok"] += c.output_tok
            agg[c.model]["cost"]       += c.total_cost

        unknown_models = [m for m in agg if m not in MODEL_PRICES]
        for model, s in agg.items():
            est = " (estimated)" if model not in MODEL_PRICES else ""
            logger.info(
                "  %-35s %3d calls  %8s in  %8s out  $%.5f%s",
                model, s["calls"],
                f"{s['input_tok']:,}", f"{s['output_tok']:,}",
                s["cost"], est,
            )
        logger.info(
            "  %-35s          %8s in  %8s out  $%.5f",
            "TOTAL", f"{self.total_input_tokens:,}", f"{self.total_output_tokens:,}",
            self.total_cost,
        )
        if unknown_models:
            in_p, out_p = _FALLBACK_PRICE
            logger.info(
                "  Note: unknown models estimated at $%.2f/$%.2f per 1M tokens",
                in_p, out_p,
            )

    def to_dict(self) -> dict:
        agg: dict[str, dict] = {}
        for c in self._calls:
            if c.model not in agg:
                agg[c.model] = {
                    "calls": 0, "input_tokens": 0, "output_tokens": 0,
                    "cost_usd": 0.0, "price_known": c.model in MODEL_PRICES,
                }
            agg[c.model]["calls"]         += 1
            agg[c.model]["input_tokens"]  += c.input_tok
            agg[c.model]["output_tokens"] += c.output_tok
            agg[c.model]["cost_usd"]      += c.total_cost

        return {
            "total_cost_usd":      round(self.total_cost, 6),
            "total_input_tokens":  self.total_input_tokens,
            "total_output_tokens": self.total_output_tokens,
            "by_model": {
                m: {**s, "cost_usd": round(s["cost_usd"], 6)}
                for m, s in agg.items()
            },
            "calls": [
                {
                    "model":        c.model,
                    "stage":        c.stage,
                    "input_tokens": c.input_tok,
                    "output_tokens":c.output_tok,
                    "cost_usd":     round(c.total_cost, 6),
                }
                for c in self._calls
            ],
        }


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def setup_logging() -> logging.Logger:
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    fmt = "%(asctime)s %(levelname)s %(message)s"
    logging.basicConfig(
        level=logging.INFO,
        format=fmt,
        handlers=[
            logging.FileHandler(LOG_FILE),
            logging.StreamHandler(),
        ],
    )
    return logging.getLogger("lab-agent")


def get_client() -> genai.Client:
    return genai.Client(api_key=GOOGLE_API_KEY)


def get_tree(path: str) -> str:
    try:
        result = subprocess.run(
            ["tree", "--noreport", "-L", "3", path],
            capture_output=True, text=True, timeout=30,
        )
        return result.stdout
    except FileNotFoundError:
        result = subprocess.run(
            ["find", path, "-type", "f", "-not", "-path", "*/.git/*"],
            capture_output=True, text=True, timeout=30,
        )
        return result.stdout


def read_file(path: str) -> str:
    try:
        with open(path, "r", errors="replace") as fh:
            return fh.read()
    except Exception as exc:
        return f"[Error reading {path}: {exc}]"


def _build_contents(messages: list) -> list[types.Content]:
    """Convert OpenAI-style message list to Google GenAI Contents (skips system)."""
    contents = []
    for msg in messages:
        role = msg["role"]
        text = msg["content"]
        if role == "system":
            continue
        google_role = "model" if role == "assistant" else "user"
        contents.append(
            types.Content(role=google_role, parts=[types.Part(text=text)])
        )
    return contents


def _extract_system(messages: list) -> str | None:
    for msg in messages:
        if msg["role"] == "system":
            return msg["content"]
    return None


def call_model(
    client: genai.Client,
    messages: list,
    model: str,
    stage: str,
    tracker: CostTracker,
    logger: logging.Logger,
) -> str:
    model_id = model.removeprefix("google/")
    logger.debug("Calling model %s with %d messages", model_id, len(messages))

    system_text = _extract_system(messages)
    config = types.GenerateContentConfig(
        system_instruction=system_text,
    ) if system_text else None

    response = client.models.generate_content(
        model=model_id,
        config=config,
        contents=_build_contents(messages),
    )

    # Record token usage for cost tracking
    usage = response.usage_metadata
    if usage:
        tracker.record(
            model=model_id,
            stage=stage,
            input_tok=usage.prompt_token_count or 0,
            output_tok=usage.candidates_token_count or 0,
        )

    return response.text or ""


# ---------------------------------------------------------------------------
# Stage 1: Ask the model which files it needs to see
# ---------------------------------------------------------------------------

def stage1(client: genai.Client, tracker: CostTracker, logger: logging.Logger):
    tree_output = get_tree(ASSIGNMENT_DIR)
    readme_path = os.path.join(ASSIGNMENT_DIR, "README.md")
    readme_text = read_file(readme_path)

    prompt = (
        f"Tree structure of the assignment directory:\n{tree_output}\n\n"
        f"README.md:\n{readme_text}\n\n"
        "You will create a plan for completing this assignment. "
        "Specify the files you need to see in order to make this plan "
        "in the following format:\n\n"
        "```output\n"
        "./myfile1.v\n"
        "./myfile2\n"
        "...\n"
        "```\n\n"
        "Output just this output code block and nothing else; "
        "we will give them back to you in the next step."
    )

    messages = [{"role": "user", "content": prompt}]
    logger.info("=== Stage 1: probing for required files ===")
    response = call_model(client, messages, MODEL_PLAN, "stage1", tracker, logger)
    logger.info("Stage 1 response:\n%s", response)

    match = re.search(r"```output\n(.*?)```", response, re.DOTALL)
    if match:
        file_list = [
            line.strip()
            for line in match.group(1).strip().splitlines()
            if line.strip()
        ]
    else:
        logger.warning("No ```output block found; requesting all .v/.vh/.cpp files")
        file_list = [
            "./fe_stage.v", "./agex_stage.v", "./de_stage.v",
            "./mem_stage.v", "./wb_stage.v", "./pipeline.v",
            "./define.vh", "./sim_main.cpp",
        ]

    logger.info("Files requested by model: %s", file_list)
    return messages, response, file_list


# ---------------------------------------------------------------------------
# Stage 2: Provide file contents and ask for a full implementation plan
# ---------------------------------------------------------------------------

def stage2(
    client: genai.Client,
    messages1: list,
    response1: str,
    file_list: list,
    tracker: CostTracker,
    logger: logging.Logger,
):
    sections = []
    for rel_path in file_list:
        clean   = rel_path.lstrip("./")
        full    = os.path.join(ASSIGNMENT_DIR, clean)
        content = read_file(full)
        sections.append(f"### {rel_path}\n```\n{content}\n```")

    files_text = "\n\n".join(sections)
    prompt = (
        f"Here are the file contents you requested:\n\n{files_text}\n\n"
        "Create the complete plan for implementing the branch predictor "
        "described in the README. Be specific about every change needed in "
        "every file, including exact signal widths, port names, and logic."
    )

    messages = messages1 + [
        {"role": "assistant", "content": response1},
        {"role": "user",      "content": prompt},
    ]

    logger.info("=== Stage 2: generating implementation plan ===")
    plan = call_model(client, messages, MODEL_PLAN, "stage2", tracker, logger)
    logger.info("Stage 2 plan:\n%s", plan)
    return messages, plan


# ---------------------------------------------------------------------------
# Stage 3 helpers: edit (full & diff) / read / test / submit
# ---------------------------------------------------------------------------

def _write_file(rel_path: str, content: str, logger: logging.Logger) -> str:
    full_path = os.path.join(ASSIGNMENT_DIR, rel_path)
    try:
        os.makedirs(os.path.dirname(full_path), exist_ok=True)
        with open(full_path, "w") as fh:
            fh.write(content)
        preview = "\n".join(content.splitlines()[:8])
        msg = f"Wrote {rel_path} ({len(content)} bytes). First 8 lines:\n{preview}"
        logger.info("Wrote %s (%d bytes)", rel_path, len(content))
        return msg
    except Exception as exc:
        msg = f"Error writing {rel_path}: {exc}"
        logger.error(msg)
        return msg


def execute_edit_full(body: str, logger: logging.Logger) -> str:
    lines        = body.split("\n", 1)
    rel_path     = lines[0].strip().lstrip("./")
    file_content = lines[1] if len(lines) > 1 else ""

    if not rel_path:
        return (
            "Error: no file path on the first line of the edit block.\n"
            "Format: ```edit\\n./path/to/file\\n<complete file content>\\n```"
        )

    if re.search(r'^<{7} ', file_content, re.MULTILINE) or \
       re.search(r'^>{7} ', file_content, re.MULTILINE):
        return (
            "Edit REJECTED: content contains diff/conflict markers "
            "(<<<<<<<  or >>>>>>>). In full edit mode write the COMPLETE final file."
        )

    return _write_file(rel_path, file_content, logger)


def execute_edit_diff(body: str, logger: logging.Logger) -> str:
    lines     = body.split("\n", 1)
    rel_path  = lines[0].strip().lstrip("./")
    diff_body = lines[1] if len(lines) > 1 else ""

    if not rel_path:
        return (
            "Error: no file path on the first line of the edit block.\n"
            "Format: ```edit\\n./path/to/file\\n<<<<<<< SEARCH\\n...\\n```"
        )

    full_path = os.path.join(ASSIGNMENT_DIR, rel_path)
    current   = read_file(full_path)
    if current.startswith("[Error"):
        return current

    blocks = _DIFF_BLOCK_RE.findall(diff_body)
    if not blocks:
        return (
            "Error: no SEARCH/REPLACE blocks found in the edit body.\n"
            "Each change must be wrapped like:\n"
            "<<<<<<< SEARCH\nexact text to find\n=======\nreplacement text\n>>>>>>> REPLACE"
        )

    result  = current
    reports = []
    applied = 0

    for search_text, replace_text in blocks:
        count = result.count(search_text)
        if count == 0:
            reports.append(
                f"SEARCH text NOT FOUND in {rel_path}:\n```\n{search_text[:300]}\n```"
            )
        elif count > 1:
            reports.append(
                f"SEARCH text is AMBIGUOUS ({count} occurrences) in {rel_path}:\n"
                f"```\n{search_text[:300]}\n```\n"
                "Make the search text more specific so it matches exactly once."
            )
        else:
            result = result.replace(search_text, replace_text, 1)
            applied += 1

    if reports:
        error_block = "\n\n".join(reports)
        if applied > 0:
            _write_file(rel_path, result, logger)
            return (
                f"Partially applied {applied}/{len(blocks)} change(s) to {rel_path}. "
                f"The following blocks failed:\n\n{error_block}"
            )
        return f"No changes applied to {rel_path}.\n\n{error_block}"

    return _write_file(rel_path, result, logger)


def execute_edit(body: str, logger: logging.Logger) -> str:
    if EDIT_MODE == "diff":
        return execute_edit_diff(body, logger)
    return execute_edit_full(body, logger)


def execute_read(body: str, logger: logging.Logger) -> str:
    rel_path = body.strip().lstrip("./")
    if not rel_path:
        return "Error: no file path provided in the read block."

    full_path = os.path.join(ASSIGNMENT_DIR, rel_path)
    content   = read_file(full_path)
    if content.startswith("[Error"):
        return content

    lines     = content.splitlines()
    MAX_LINES = 150
    if len(lines) > MAX_LINES:
        shown  = "\n".join(lines[:MAX_LINES])
        result = (
            f"Contents of {rel_path} (first {MAX_LINES} of {len(lines)} lines):\n"
            f"```\n{shown}\n... ({len(lines) - MAX_LINES} more lines)\n```"
        )
    else:
        result = f"Contents of {rel_path} ({len(lines)} lines):\n```\n{content}\n```"

    logger.info("Read %s (%d lines)", rel_path, len(lines))
    return result


def execute_test(logger: logging.Logger) -> str:
    all_output = []
    for part in ("part4", "part2"):
        logger.info("Running %s tests ...", part)
        result = subprocess.run(
            ["bash", "run_tests.sh", part],
            cwd=ASSIGNMENT_DIR,
            capture_output=True,
            text=True,
            timeout=600,
        )

        build_failed = "%Error:" in result.stderr
        if build_failed:
            section = (
                f"=== {part} tests ===\n"
                f"BUILD FAILED – Verilator reported errors (no tests ran):\n"
                f"{result.stderr[:3000]}"
            )
        else:
            section = f"=== {part} tests ===\n{result.stdout}"
            results_log = os.path.join(ASSIGNMENT_DIR, f"{part}_results.log")
            if os.path.exists(results_log):
                section += "\n--- per-test results ---\n" + read_file(results_log)
            if result.stderr.strip():
                section += f"\n--- stderr ---\n{result.stderr[:2000]}"

        all_output.append(section)
        logger.info("%s summary:\n%s", part, result.stdout)

    return "\n\n".join(all_output)


# ---------------------------------------------------------------------------
# Stage 3 system prompts (one per edit mode)
# ---------------------------------------------------------------------------

_STAGE3_SYSTEM_BASE = """\
You are implementing a G-share branch predictor for a RISC-V CPU pipeline \
(CS3220 Lab 2). Work methodically: edit files, run tests, fix issues, repeat.

You may output MULTIPLE code blocks in a single response. \
All ```edit and ```read blocks are processed in order before feedback is returned. \
Use this to modify several files at once when a change spans multiple files.

{edit_section}
  ```read
  ./path/to/file
  ```
  Read the current on-disk contents of a file.
  Multiple ```read blocks are allowed in one response.

  ```test
  ```
  Run the test suite and receive pass/fail results.
  Must be the LAST block in a response (nothing after it is processed).
  No content inside this block.

  ```submit
  ```
  Mark the assignment as complete. Only use once all tests pass.
  Must be the LAST block in a response.

IMPORTANT: Use ONLY the fence types listed above. \
Do NOT use ```verilog, ```c, ```cpp, or any other language identifier.
"""

_EDIT_SECTION_FULL = """\
Available actions:

  ```edit
  ./path/to/file
  <complete new file content>
  ```
  Write (or overwrite) the file with the COMPLETE content.
  Multiple ```edit blocks are allowed in one response to update several files at once.
  RULES:
  - First line MUST be the file path (e.g. ./define.vh)
  - All remaining lines are the ENTIRE new file – every line, nothing omitted
  - NEVER use diff/patch format or conflict markers (<<<<<<<, =======, >>>>>>>)
  - Always write the full file from scratch
"""

_EDIT_SECTION_DIFF = """\
Available actions:

  ```edit
  ./path/to/file
  <<<<<<< SEARCH
  exact text to find (must match the file exactly, including whitespace)
  =======
  replacement text
  >>>>>>> REPLACE
  ```
  Apply targeted search-and-replace edits to a file.
  Multiple ```edit blocks are allowed in one response to update several files at once.
  RULES:
  - First line MUST be the file path (e.g. ./define.vh)
  - Use one or more SEARCH/REPLACE pairs (applied top-to-bottom)
  - SEARCH text must appear EXACTLY ONCE in the file; make it specific enough
  - Include enough surrounding context (3–5 lines) to ensure uniqueness
  - You will be told if a search text is not found or is ambiguous
"""

STAGE3_SYSTEM = _STAGE3_SYSTEM_BASE.format(
    edit_section=_EDIT_SECTION_DIFF if EDIT_MODE == "diff" else _EDIT_SECTION_FULL
)


# ---------------------------------------------------------------------------
# Stage 3: Execution loop
# ---------------------------------------------------------------------------

def _dispatch_block(action: str, body: str, logger: logging.Logger) -> tuple[str, bool, bool]:
    """Process one parsed code block.

    Returns (result_text, is_terminal, submitted).
    is_terminal → stop processing further blocks this iteration.
    submitted   → exit the outer loop entirely.
    """
    if action == "submit":
        logger.info("=== SUBMITTED – agent complete ===")
        return "", True, True

    if action == "edit":
        return execute_edit(body, logger), False, False

    if action == "read":
        return execute_read(body, logger), False, False

    if action == "test":
        return execute_test(logger), True, False

    if action in LANG_FENCES:
        msg = (
            f"Invalid fence type '```{action}'. "
            "To write a file use:\n"
            "```edit\n./path/to/file\n<…>\n```\n"
            "Valid fence types are: edit, read, test, submit."
        )
        logger.warning("Model used language fence '%s' instead of 'edit'", action)
        return msg, False, False

    msg = f"Unknown action '{action}'. Valid actions are: edit, read, test, submit."
    logger.warning("Unknown action: %s", action)
    return msg, False, False


def stage3(
    client: genai.Client,
    messages2: list,
    plan: str,
    tracker: CostTracker,
    logger: logging.Logger,
):
    kickoff = (
        "The plan is ready. Now implement it step by step.\n"
        "You may output multiple code blocks in one response to edit several files at once.\n"
        "Start by reading the files you need to modify, then edit them."
    )

    messages = (
        [{"role": "system", "content": STAGE3_SYSTEM}]
        + messages2
        + [
            {"role": "assistant", "content": plan},
            {"role": "user",      "content": kickoff},
        ]
    )

    logger.info("=== Stage 3: execution loop (max %d iterations) ===", MAX_ITERATIONS)

    for iteration in range(1, MAX_ITERATIONS + 1):
        logger.info("--- Iteration %d ---", iteration)

        response = call_model(client, messages, MODEL_LOOP, f"stage3.iter{iteration}", tracker, logger)
        logger.info("Model:\n%s", response)

        blocks = list(re.finditer(r"```(\w+)\n?(.*?)```", response, re.DOTALL))
        if not blocks:
            feedback = (
                "No code blocks found in your response. "
                "Output one or more code blocks using ```edit, ```read, ```test, or ```submit."
            )
            logger.warning("No code blocks – sending feedback")
            messages = messages + [
                {"role": "assistant", "content": response},
                {"role": "user",      "content": feedback},
            ]
            continue

        results = []
        done    = False

        for m in blocks:
            action = m.group(1).strip().lower()
            body   = m.group(2)

            result, terminal, submitted = _dispatch_block(action, body, logger)

            if submitted:
                done = True
                break

            if result:
                logger.info("Result for '%s' (first 500 chars):\n%s", action, result[:500])
                results.append(f"[{action}] {result}")

            if terminal:
                break

        if done:
            break

        feedback = "\n\n".join(results) if results else "(all blocks processed with no output)"
        messages = messages + [
            {"role": "assistant", "content": response},
            {"role": "user",      "content": feedback},
        ]
    else:
        logger.warning("Max iterations (%d) reached without submit.", MAX_ITERATIONS)


# ---------------------------------------------------------------------------
# Output finalisation
# ---------------------------------------------------------------------------

def save_output(tracker: CostTracker, logger: logging.Logger) -> None:
    """Copy final assignment files and write cost report into OUTPUT_DIR."""

    # Cost report (JSON)
    cost_path = os.path.join(OUTPUT_DIR, "costs.json")
    try:
        with open(cost_path, "w") as fh:
            json.dump(tracker.to_dict(), fh, indent=2)
        logger.info("Cost report written to %s", cost_path)
    except Exception as exc:
        logger.error("Failed to write cost report: %s", exc)

    # Copy final assignment files (skip hidden dirs and test .log files)
    out_assignment = os.path.join(OUTPUT_DIR, "assignment")
    try:
        if os.path.exists(out_assignment):
            shutil.rmtree(out_assignment)
        shutil.copytree(
            ASSIGNMENT_DIR,
            out_assignment,
            ignore=shutil.ignore_patterns(".*", "__pycache__"),
        )
        logger.info("Final assignment files copied to %s", out_assignment)
    except Exception as exc:
        logger.error("Failed to copy assignment files: %s", exc)


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main() -> int:
    logger = setup_logging()
    logger.info("============================================================")
    logger.info("Lab Agent starting")
    logger.info("Model (plan):   %s", MODEL_PLAN)
    logger.info("Model (loop):   %s", MODEL_LOOP)
    logger.info("Edit mode:      %s", EDIT_MODE)
    logger.info("Assignment dir: %s", ASSIGNMENT_DIR)
    logger.info("Output dir:     %s", OUTPUT_DIR)
    logger.info("Max iterations: %d", MAX_ITERATIONS)
    logger.info("============================================================")

    if not GOOGLE_API_KEY:
        logger.error("GOOGLE_API_KEY is not set – aborting.")
        return 1

    if EDIT_MODE not in ("full", "diff"):
        logger.error("EDIT_MODE must be 'full' or 'diff', got: %s", EDIT_MODE)
        return 1

    tracker = CostTracker()
    client  = get_client()

    messages1, response1, file_list = stage1(client, tracker, logger)
    messages2, plan = stage2(client, messages1, response1, file_list, tracker, logger)
    stage3(client, messages2, plan, tracker, logger)

    tracker.log_summary(logger)
    save_output(tracker, logger)

    logger.info("============================================================")
    logger.info("Lab Agent finished")
    logger.info("============================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
