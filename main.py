#!/usr/bin/env python3
"""
Lab Agent - Completes CS3220 Lab #2 (Branch Prediction) using an LLM via OpenRouter.

Pipeline:
  Stage 1 (planning probe): Give the model tree + README; it lists files it needs.
  Stage 2 (planning):       Give the model the file contents; it writes a plan.
  Stage 3 (execution loop): The model iteratively edits files, runs tests, and submits.

Environment variables:
  OPENROUTER_API_KEY  – required
  MODEL_PLAN          – model for stages 1+2  (default: google/gemini-3.1-pro-preview)
  MODEL_LOOP          – model for stage 3 loop (default: google/gemini-3-flash-preview)
  MODEL               – overrides both MODEL_PLAN and MODEL_LOOP if set
  EDIT_MODE           – "full" (default) or "diff"
  ASSIGNMENT_DIR      – path to the assignment directory (default: /app/assignment)
  LOG_DIR             – path where agent.log is written (default: /logs)
  MAX_ITERATIONS      – stage-3 iteration cap (default: 60)
"""

import os
import re
import subprocess
import logging

from openai import OpenAI

# ---------------------------------------------------------------------------
# Configuration (can be overridden via environment variables)
# ---------------------------------------------------------------------------
OPENROUTER_API_KEY = os.environ.get("OPENROUTER_API_KEY", "")

_model_override = os.environ.get("MODEL", "")
MODEL_PLAN = _model_override or os.environ.get("MODEL_PLAN", "google/gemini-3.1-pro-preview")
MODEL_LOOP = _model_override or os.environ.get("MODEL_LOOP", "google/gemini-3-flash-preview")

EDIT_MODE      = os.environ.get("EDIT_MODE", "full")   # "full" | "diff"
ASSIGNMENT_DIR = os.environ.get("ASSIGNMENT_DIR", "/app/assignment")
LOG_DIR        = os.environ.get("LOG_DIR", "/logs")
MAX_ITERATIONS = int(os.environ.get("MAX_ITERATIONS", "60"))

# Language fence names the model might mistakenly use instead of ```edit
LANG_FENCES = {
    'verilog', 'v', 'sv', 'systemverilog', 'c', 'cpp', 'c++', 'cxx',
    'python', 'py', 'bash', 'sh', 'shell', 'js', 'javascript',
    'ts', 'typescript', 'json', 'yaml', 'toml', 'text', 'txt', 'plaintext',
}

# Markers used by the diff-mode SEARCH/REPLACE format
_DIFF_SEARCH  = "<<<<<<< SEARCH"
_DIFF_SEP     = "======="
_DIFF_REPLACE = ">>>>>>> REPLACE"

# Regex to find all SEARCH/REPLACE blocks inside an edit body
_DIFF_BLOCK_RE = re.compile(
    r"<<<<<<< SEARCH\n(.*?)\n=======\n(.*?)\n>>>>>>> REPLACE",
    re.DOTALL,
)


# ---------------------------------------------------------------------------
# Helpers
# ---------------------------------------------------------------------------

def setup_logging() -> logging.Logger:
    os.makedirs(LOG_DIR, exist_ok=True)
    fmt = "%(asctime)s %(levelname)s %(message)s"
    logging.basicConfig(
        level=logging.INFO,
        format=fmt,
        handlers=[
            logging.FileHandler(os.path.join(LOG_DIR, "agent.log")),
            logging.StreamHandler(),
        ],
    )
    return logging.getLogger("lab-agent")


def get_client() -> OpenAI:
    return OpenAI(
        base_url="https://openrouter.ai/api/v1",
        api_key=OPENROUTER_API_KEY,
    )


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


def call_model(
    client: OpenAI,
    messages: list,
    model: str,
    logger: logging.Logger,
) -> str:
    logger.debug("Calling model %s with %d messages", model, len(messages))
    response = client.chat.completions.create(
        model=model,
        messages=messages,
    )
    return response.choices[0].message.content or ""


# ---------------------------------------------------------------------------
# Stage 1: Ask the model which files it needs to see
# ---------------------------------------------------------------------------

def stage1(client: OpenAI, logger: logging.Logger):
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
    response = call_model(client, messages, MODEL_PLAN, logger)
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
    client: OpenAI,
    messages1: list,
    response1: str,
    file_list: list,
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
    plan = call_model(client, messages, MODEL_PLAN, logger)
    logger.info("Stage 2 plan:\n%s", plan)
    return messages, plan


# ---------------------------------------------------------------------------
# Stage 3 helpers: edit (full & diff) / read / test / submit
# ---------------------------------------------------------------------------

def _write_file(rel_path: str, content: str, logger: logging.Logger) -> str:
    """Write content to ASSIGNMENT_DIR/rel_path; return a status message."""
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
    """Full-file overwrite mode.

    Block format:
        ```edit
        ./path/to/file
        <complete new file content>
        ```
    """
    lines = body.split("\n", 1)
    rel_path     = lines[0].strip().lstrip("./")
    file_content = lines[1] if len(lines) > 1 else ""

    if not rel_path:
        return (
            "Error: no file path on the first line of the edit block.\n"
            "Format: ```edit\\n./path/to/file\\n<complete file content>\\n```"
        )

    # Reject diff/conflict-marker content in full mode
    if re.search(r'^<{7} ', file_content, re.MULTILINE) or \
       re.search(r'^>{7} ', file_content, re.MULTILINE):
        return (
            "Edit REJECTED: content contains diff/conflict markers "
            "(<<<<<<<  or >>>>>>>). In full edit mode you must write the "
            "COMPLETE final file – not a diff or patch. "
            "Remove all markers and write the full file from scratch. "
            "Alternatively, switch to diff mode with the ```edit SEARCH/REPLACE format."
        )

    return _write_file(rel_path, file_content, logger)


def execute_edit_diff(body: str, logger: logging.Logger) -> str:
    """Search/replace diff mode.

    Block format (one or more SEARCH/REPLACE pairs):
        ```edit
        ./path/to/file
        <<<<<<< SEARCH
        exact text to find
        =======
        replacement text
        >>>>>>> REPLACE
        ```

    Rules:
    - SEARCH text must appear exactly once in the file.
    - Multiple pairs are applied top-to-bottom in a single pass.
    """
    lines = body.split("\n", 1)
    rel_path      = lines[0].strip().lstrip("./")
    diff_body     = lines[1] if len(lines) > 1 else ""

    if not rel_path:
        return (
            "Error: no file path on the first line of the edit block.\n"
            "Format: ```edit\\n./path/to/file\\n<<<<<<< SEARCH\\n...\\n=======\\n...\\n>>>>>>> REPLACE\\n```"
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
                f"SEARCH text NOT FOUND in {rel_path}:\n"
                f"```\n{search_text[:300]}\n```"
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
            # Some blocks succeeded – still write partial changes
            _write_file(rel_path, result, logger)
            return (
                f"Partially applied {applied}/{len(blocks)} change(s) to {rel_path}. "
                f"The following blocks failed:\n\n{error_block}"
            )
        else:
            return f"No changes applied to {rel_path}.\n\n{error_block}"

    return _write_file(rel_path, result, logger)


def execute_edit(body: str, logger: logging.Logger) -> str:
    if EDIT_MODE == "diff":
        return execute_edit_diff(body, logger)
    return execute_edit_full(body, logger)


def execute_read(body: str, logger: logging.Logger) -> str:
    """Return the current contents of a file (capped at 150 lines)."""
    rel_path = body.strip().lstrip("./")
    if not rel_path:
        return "Error: no file path provided in the read block."

    full_path = os.path.join(ASSIGNMENT_DIR, rel_path)
    content   = read_file(full_path)
    if content.startswith("[Error"):
        return content

    lines    = content.splitlines()
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
    """Run part4 and part2 test suites and return combined output."""
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
            stderr_excerpt = result.stderr[:3000]
            section = (
                f"=== {part} tests ===\n"
                f"BUILD FAILED – Verilator reported errors (no tests ran):\n"
                f"{stderr_excerpt}"
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
Output EXACTLY ONE code block per response and NOTHING else outside it.

{edit_section}
  ```read
  ./path/to/file
  ```
  Read the current on-disk contents of a file.

  ```test
  ```
  Run the test suite. (No content inside this block.)

  ```submit
  ```
  Mark the assignment as complete. Only use once all tests pass.

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
  Apply targeted search-and-replace edits to the file.
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

def stage3(
    client: OpenAI,
    messages2: list,
    plan: str,
    logger: logging.Logger,
):
    kickoff = (
        "The plan is ready. Now implement it step by step.\n"
        "Output EXACTLY ONE code block per response and NOTHING else outside it.\n"
        "Start by reading the first file you need to modify, then edit it."
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

        response = call_model(client, messages, MODEL_LOOP, logger)
        logger.info("Model:\n%s", response)

        match = re.search(r"```(\w+)\n?(.*?)```", response, re.DOTALL)
        if not match:
            feedback = (
                "No code block found in your response. "
                "Output EXACTLY ONE code block using ```edit, ```read, ```test, or ```submit."
            )
            logger.warning("No code block – sending feedback")
            messages = messages + [
                {"role": "assistant", "content": response},
                {"role": "user",      "content": feedback},
            ]
            continue

        action = match.group(1).strip().lower()
        body   = match.group(2)

        if action == "submit":
            logger.info("=== SUBMITTED – agent complete ===")
            break

        elif action == "edit":
            result = execute_edit(body, logger)

        elif action == "read":
            result = execute_read(body, logger)

        elif action == "test":
            result = execute_test(logger)

        elif action in LANG_FENCES:
            result = (
                f"Invalid fence type '```{action}'. "
                "To write a file use:\n"
                "```edit\n./path/to/file\n<…>\n```\n"
                "Valid fence types are: edit, read, test, submit."
            )
            logger.warning("Model used language fence '%s' instead of 'edit'", action)

        else:
            result = (
                f"Unknown action '{action}'. "
                "Valid actions are: edit, read, test, submit."
            )
            logger.warning("Unknown action: %s", action)

        logger.info("Result (first 500 chars):\n%s", result[:500])
        messages = messages + [
            {"role": "assistant", "content": response},
            {"role": "user",      "content": result},
        ]
    else:
        logger.warning("Max iterations (%d) reached without submit.", MAX_ITERATIONS)


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
    logger.info("Log dir:        %s", LOG_DIR)
    logger.info("Max iterations: %d", MAX_ITERATIONS)
    logger.info("============================================================")

    if not OPENROUTER_API_KEY:
        logger.error("OPENROUTER_API_KEY is not set – aborting.")
        return 1

    if EDIT_MODE not in ("full", "diff"):
        logger.error("EDIT_MODE must be 'full' or 'diff', got: %s", EDIT_MODE)
        return 1

    client = get_client()

    messages1, response1, file_list = stage1(client, logger)
    messages2, plan = stage2(client, messages1, response1, file_list, logger)
    stage3(client, messages2, plan, logger)

    logger.info("============================================================")
    logger.info("Lab Agent finished")
    logger.info("============================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
