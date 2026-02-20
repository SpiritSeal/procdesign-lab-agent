# lab-agent

An LLM agent that autonomously completes a hardware design lab assignment — specifically, implementing a G-share branch predictor for a RISC-V pipeline (CS3220 Lab 2) — using Google Gemini via the native Generative AI API.

The agent runs inside Docker, edits Verilog source files, compiles and tests them with Verilator, and iterates until all tests pass. Each run produces a self-contained output directory with the agent log, a per-call cost breakdown, and a snapshot of the final source files.

## How it works

The agent follows a fixed three-stage pipeline:

```
Stage 1  [gemini-3.1-pro-preview]
  Given: directory tree + README
  Output: list of files it needs to read

Stage 2  [gemini-3.1-pro-preview]
  Given: contents of requested files
  Output: detailed implementation plan

Stage 3  [gemini-3-flash-preview]  ← iterates up to MAX_ITERATIONS times
  Loop:
    Model emits one or more code blocks
    Agent executes each block in order:
      ```edit   – write or patch a file
      ```read   – read a file's current contents
      ```test   – compile with Verilator and run test suite
      ```submit – declare done and exit
    Agent sends combined results back as the next user message
```

The planning stages use the most capable model; the execution loop uses a faster, cheaper model since it makes many calls.

### Edit modes

Two strategies are supported via `EDIT_MODE`:

| Mode | `EDIT_MODE` | Description |
|------|-------------|-------------|
| Full rewrite | `full` (default) | Model writes the entire file content |
| Search/replace | `diff` | Model provides `<<<<<<< SEARCH / ======= / >>>>>>> REPLACE` blocks; agent applies them surgically |

Diff mode is less likely to accidentally drop lines in large files. Full mode is simpler and more reliable for new files.

## Quickstart

**Prerequisites:** Docker, `make`, a Google AI API key.

```bash
# 1. Clone
git clone <repo-url>
cd lab-agent

# 2. Add your API key
echo "GOOGLE_API_KEY=your_key_here" > .env

# 3. Build and run
make run
```

Output lands in `logs/run_YYYYMMDD_HHMMSS/`.

## Output structure

Each run produces a timestamped directory:

```
logs/
└── run_20260219_203045/
    ├── agent.log       ← full execution transcript with cost summary at end
    ├── costs.json      ← machine-readable token usage and USD cost per API call
    └── assignment/     ← snapshot of every file as the agent left them
        ├── define.vh
        ├── fe_stage.v
        ├── agex_stage.v
        └── ...
```

The original `./assignment/` source on the host is never modified — the agent works on the copy baked into the Docker image.

**`costs.json` structure:**
```json
{
  "total_cost_usd": 0.0382,
  "total_input_tokens": 241840,
  "total_output_tokens": 8193,
  "by_model": {
    "gemini-3.1-pro-preview": { "calls": 2, "input_tokens": 28400, "cost_usd": 0.012 },
    "gemini-3-flash-preview":  { "calls": 21, "input_tokens": 213440, "cost_usd": 0.026 }
  },
  "calls": [
    { "model": "gemini-3.1-pro-preview", "stage": "stage1", "input_tokens": 3210, ... },
    ...
  ]
}
```

Pricing is taken from a table in `main.py` (`MODEL_PRICES`). Preview models are labeled as estimates in the log.

## Configuration

All options are environment variables. Set them in `.env` or pass on the command line:

| Variable | Default | Description |
|----------|---------|-------------|
| `GOOGLE_API_KEY` | — | **Required.** Google AI API key |
| `MODEL_PLAN` | `gemini-3.1-pro-preview` | Model for stages 1 & 2 |
| `MODEL_LOOP` | `gemini-3-flash-preview` | Model for the stage 3 execution loop |
| `MODEL` | — | Overrides both `MODEL_PLAN` and `MODEL_LOOP` |
| `EDIT_MODE` | `full` | `full` or `diff` |
| `MAX_ITERATIONS` | `60` | Stage 3 iteration cap |

**Command-line overrides:**
```bash
make run EDIT_MODE=diff
make run MODEL_LOOP=gemini-3.1-pro-preview EDIT_MODE=diff
make run MODEL=gemini-2.0-flash MAX_ITERATIONS=30
```

## Makefile targets

```
make build   build the Docker image
make run     build and run the agent
make logs    tail the most recent agent.log
make clean   remove the Docker image and logs/ directory
```

## The assignment

`./assignment/` contains a partial RISC-V pipeline implementation (Verilog + Verilator harness). The agent's task is to implement a G-share branch predictor across four files:

- **`define.vh`** — latch width constants and new BTB/PHT/BHR parameters
- **`fe_stage.v`** — BTB lookup, PHT prediction, next-PC selection, update logic
- **`agex_stage.v`** — misprediction detection, flush signal, BTB/PHT/BHR update forwarding, accuracy counters
- **`sim_main.cpp`** — read Verilator-public counter registers and print `Accuracy=xx%`

Tests are run via `run_tests.sh` against the `part2` and `part4` test suites using Verilator.

## Robustness features

Several failure modes were observed in early runs and are explicitly handled:

- **Wrong fence type** — if the model uses ` ```verilog ` instead of ` ```edit `, the agent rejects it and returns a correction message
- **Diff format in full mode** — content containing `<<<<<<<`/`>>>>>>>` markers is rejected before writing to disk
- **Build failure visibility** — when Verilator reports `%Error:`, the agent surfaces a `BUILD FAILED` banner with the full stderr rather than the misleading "0 passed / 0 failed" output
- **File inspection** — the `read` action lets the model check the current on-disk state of any file before editing it

## Project structure

```
lab-agent/
├── main.py          agent implementation
├── Dockerfile
├── Makefile
├── pyproject.toml
├── assignment/      lab source files (Verilog, C++, test vectors)
├── logs/            run output (gitignored by default except .gitkeep)
└── REVISIONS.md     changelog of agent iterations based on log analysis
```

## Iteration log

`REVISIONS.md` documents the changes made to the agent after each observed run, including root-cause analysis of failures and the specific fixes applied. It serves as a record of the agent development process.
