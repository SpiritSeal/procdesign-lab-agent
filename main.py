#!/usr/bin/env python3
"""
Lab Agent - Completes CS3220 Lab #2 (Branch Prediction) using an LLM via OpenRouter.

Pipeline:
  Stage 1 (planning probe): Give the model tree + README; it lists files it needs.
  Stage 2 (planning):       Give the model the file contents; it writes a plan.
  Stage 3 (execution loop): The model iteratively edits files, runs tests, and submits.
"""

import os
import re
import subprocess
import logging
from pathlib import Path

from openai import OpenAI

# ---------------------------------------------------------------------------
# Configuration (can be overridden via environment variables)
# ---------------------------------------------------------------------------
OPENROUTER_API_KEY = os.environ.get("OPENROUTER_API_KEY", "")
MODEL              = os.environ.get("MODEL", "anthropic/claude-sonnet-4-6")
ASSIGNMENT_DIR     = os.environ.get("ASSIGNMENT_DIR", "/app/assignment")
LOG_DIR            = os.environ.get("LOG_DIR", "/logs")
MAX_ITERATIONS     = int(os.environ.get("MAX_ITERATIONS", "60"))


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


def call_model(client: OpenAI, messages: list, logger: logging.Logger) -> str:
    logger.debug("Calling model %s with %d messages", MODEL, len(messages))
    response = client.chat.completions.create(
        model=MODEL,
        messages=messages,
    )
    content = response.choices[0].message.content or ""
    return content


# ---------------------------------------------------------------------------
# Stage 1: Ask the model which files it needs to see
# ---------------------------------------------------------------------------

def stage1(client: OpenAI, logger: logging.Logger):
    tree_output  = get_tree(ASSIGNMENT_DIR)
    readme_path  = os.path.join(ASSIGNMENT_DIR, "README.md")
    readme_text  = read_file(readme_path)

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
    response = call_model(client, messages, logger)
    logger.info("Stage 1 response:\n%s", response)

    # Parse the file list from ```output ... ``` block
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
    # Read each requested file
    sections = []
    for rel_path in file_list:
        clean = rel_path.lstrip("./")
        full  = os.path.join(ASSIGNMENT_DIR, clean)
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
    plan = call_model(client, messages, logger)
    logger.info("Stage 2 plan:\n%s", plan)
    return messages, plan


# ---------------------------------------------------------------------------
# Stage 3 helpers: edit / test / submit
# ---------------------------------------------------------------------------

def execute_edit(body: str, logger: logging.Logger) -> str:
    """Parse and apply an edit action.

    Format:
        ```edit
        ./path/to/file
        <full file content>
        ```
    """
    lines = body.split("\n", 1)
    if not lines:
        return "Error: empty edit block"

    rel_path    = lines[0].strip().lstrip("./")
    file_content = lines[1] if len(lines) > 1 else ""

    full_path = os.path.join(ASSIGNMENT_DIR, rel_path)
    try:
        os.makedirs(os.path.dirname(full_path), exist_ok=True)
        with open(full_path, "w") as fh:
            fh.write(file_content)
        msg = f"Wrote {rel_path} ({len(file_content)} bytes)"
        logger.info(msg)
        return msg
    except Exception as exc:
        msg = f"Error writing {rel_path}: {exc}"
        logger.error(msg)
        return msg


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

        section = f"=== {part} tests ===\n{result.stdout}"

        # Append the results log if it was produced
        results_log = os.path.join(ASSIGNMENT_DIR, f"{part}_results.log")
        if os.path.exists(results_log):
            section += "\n--- per-test results ---\n" + read_file(results_log)

        if result.stderr.strip():
            # Truncate long stderr (usually just compile warnings)
            stderr_excerpt = result.stderr[:2000]
            section += f"\n--- stderr (truncated) ---\n{stderr_excerpt}"

        all_output.append(section)
        logger.info("%s summary:\n%s", part, result.stdout)

    return "\n\n".join(all_output)


# ---------------------------------------------------------------------------
# Stage 3: Execution loop
# ---------------------------------------------------------------------------

STAGE3_SYSTEM = """\
You are implementing a G-share branch predictor for a RISC-V CPU pipeline \
(CS3220 Lab 2). Work methodically: edit files, run tests, fix issues, repeat. \
Output EXACTLY ONE code block per response and NOTHING else outside it.

Actions:
  ```edit
  ./path/to/file
  <complete new file content>
  ```
  Write (or overwrite) the given file with the full content.

  ```test
  ```
  Run the test suite. You will receive pass/fail results.

  ```submit
  ```
  Mark the assignment as complete. Only use this when all tests pass.
"""


def stage3(
    client: OpenAI,
    messages2: list,
    plan: str,
    logger: logging.Logger,
):
    kickoff = (
        "The plan is ready. Now implement it step by step.\n"
        "Output EXACTLY ONE code block per response and NOTHING else outside it.\n"
        "Start by editing the first file."
    )

    messages = messages2 + [
        {"role": "assistant", "content": plan},
        {"role": "user",      "content": kickoff},
    ]

    logger.info("=== Stage 3: execution loop (max %d iterations) ===", MAX_ITERATIONS)

    for iteration in range(1, MAX_ITERATIONS + 1):
        logger.info("--- Iteration %d ---", iteration)

        response = call_model(client, messages, logger)
        logger.info("Model:\n%s", response)

        # Find the first code block
        match = re.search(r"```(\w+)\n?(.*?)```", response, re.DOTALL)
        if not match:
            feedback = (
                "No code block found in your response. "
                "Please output EXACTLY ONE code block using ```edit, ```test, or ```submit."
            )
            logger.warning("No code block – sending feedback")
            messages = messages + [
                {"role": "assistant", "content": response},
                {"role": "user",      "content": feedback},
            ]
            continue

        action = match.group(1).strip().lower()
        body   = match.group(2)  # everything between the backticks

        if action == "submit":
            logger.info("=== SUBMITTED – agent complete ===")
            break

        elif action == "edit":
            result = execute_edit(body, logger)

        elif action == "test":
            result = execute_test(logger)

        else:
            result = (
                f"Unknown action '{action}'. "
                "Valid actions are: edit, test, submit."
            )
            logger.warning(result)

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
    logger.info("Model:          %s", MODEL)
    logger.info("Assignment dir: %s", ASSIGNMENT_DIR)
    logger.info("Log dir:        %s", LOG_DIR)
    logger.info("Max iterations: %d", MAX_ITERATIONS)
    logger.info("============================================================")

    if not OPENROUTER_API_KEY:
        logger.error("OPENROUTER_API_KEY is not set – aborting.")
        return 1

    client = get_client()

    # Stage 1 – probe
    messages1, response1, file_list = stage1(client, logger)

    # Stage 2 – plan
    messages2, plan = stage2(client, messages1, response1, file_list, logger)

    # Stage 3 – execute
    stage3(client, messages2, plan, logger)

    logger.info("============================================================")
    logger.info("Lab Agent finished")
    logger.info("============================================================")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
