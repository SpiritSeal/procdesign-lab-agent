# Agent Revisions

## Run Analysis (2026-02-19)

The agent ran for 37 iterations (max 60) and never passed any tests.
All failures trace back to two root-cause mistakes made in iterations 1 and 2.

---

### Issue 1 — Wrong code fence type (`verilog` instead of `edit`)

**Observed:** Iteration 1, the model output ` ```verilog ` instead of ` ```edit `.
The action parser hit the `else: unknown action` branch and discarded the write.

**Fix:** Added `LANG_FENCES` set (`verilog`, `c`, `cpp`, `python`, etc.).
When the model uses a language fence the agent now returns a clear rejection message:
> "Invalid fence type `\`\`\`verilog`. To write a file use: `\`\`\`edit\n./path/to/file\n…`"

The system prompt was also updated to explicitly state:
> "Do NOT use ` ```verilog `, ` ```c `, ` ```cpp `, or any other language identifier."

---

### Issue 2 — Diff/conflict-marker format instead of full file content

**Observed:** Iteration 2, the model wrote `<<<<<<< ORIGINAL … >>>>>>> UPDATED`
conflict-marker style diffs into `define.vh`. The agent wrote this verbatim to disk.
Every subsequent Verilator invocation then failed with:
```
%Error: define.vh:1:1: Version control conflict marker in file
```
This error persisted for all 35+ remaining iterations despite the model repeatedly
trying (and failing) to fix it, because each new edit also used conflict markers.

**Fix (two-pronged):**
1. `execute_edit` now validates the body before writing. If it contains `<<<<<<<`
   or `>>>>>>>`, the write is rejected and the model receives:
   > "Edit REJECTED: file content contains diff/conflict markers. Write the COMPLETE,
   > final file content – not a diff or patch."
2. The system prompt explicitly prohibits this format under the edit rules:
   > "NEVER use diff/patch format. NEVER use `<<<<<<<`, `=======`, or `>>>>>>>` markers."

---

### Issue 3 — "0 passed / 0 failed" obscures build failures

**Observed:** When Verilator compilation failed, `run_tests.sh` still reported
`Number of passed tests: 0 / Number of failed tests: 0` because no test binary
was produced and no "Passed"/"Failed" strings appeared in the output.
The model had no clear signal that tests couldn't run due to a build error.

**Fix:** `execute_test` now checks `result.stderr` for `%Error:`. When found, it
replaces the normal output with:
```
BUILD FAILED – Verilator reported errors (no tests ran):
<stderr up to 3000 chars>
```
The stderr budget was also raised from 2000 → 3000 chars for this path.

---

### Issue 4 — No way to inspect current on-disk file state

**Observed:** After corruption, the model would re-write files but had no way to
verify what was actually on disk. This caused repeated blind edits that failed the
same way.

**Fix:** Added a `read` action:
```
```read
./path/to/file
```
```
Returns the current file contents (capped at 150 lines). The system prompt and
kickoff message now instruct the model to read a file before editing it.

---

### Issue 5 — System prompt not injected as a system-role message

**Observed:** `STAGE3_SYSTEM` was defined but not passed to the model at all in
stage3. The action rules existed only in the code, not in the conversation.

**Fix:** `stage3` now prepends `{"role": "system", "content": STAGE3_SYSTEM}` to
the message list before the first API call.

---

## Summary of code changes (`main.py`)

| Location | Change |
|---|---|
| `LANG_FENCES` constant | New set of language fence names that are not valid actions |
| `CONFLICT_MARKERS` constant | Strings indicating diff/patch content |
| `execute_edit` | Rejects writes containing conflict markers; echoes first 8 lines of written content |
| `execute_read` | New function – reads a file and returns contents (≤150 lines) |
| `execute_test` | Detects build failure via `%Error:` in stderr; emits `BUILD FAILED` banner |
| `STAGE3_SYSTEM` | Expanded to include `read` action docs, explicit diff/lang-fence prohibitions |
| `stage3` | Injects system message; handles `read` action; handles lang-fence rejection; kickoff message updated |

---

## Changes (2026-02-19, iteration 2)

### Diff edit mode (`EDIT_MODE=diff`)

Added a second edit strategy selectable via `EDIT_MODE` env var (`full` | `diff`, default `full`).

**Motivation:** Full-file rewrites of large Verilog files are expensive and error-prone
(the model may drop or corrupt lines far from the actual change). Search/replace edits
allow targeted, minimal changes while leaving the rest of the file untouched.

**Format** (one or more pairs per block):
```
```edit
./path/to/file
<<<<<<< SEARCH
exact text to find
=======
replacement text
>>>>>>> REPLACE
```
```

**Implementation** (`execute_edit_diff`):
- Parses all `<<<<<<< SEARCH … ======= … >>>>>>> REPLACE` blocks via regex
- Each search text must appear **exactly once** in the file (ambiguous matches are rejected)
- Applies replacements top-to-bottom in a single pass
- Returns detailed feedback on any search texts that are not found or are ambiguous
- Partial application: if some blocks succeed and others fail, the successful ones are
  written and the model is told which blocks still need fixing

**Conflict marker check in full mode** was tightened to look for lines starting with
`^<{7} ` or `^>{7} ` (7 angle brackets followed by a space) via regex, reducing the
chance of false positives on legitimate file content.

---

### Per-stage models (`MODEL_PLAN` / `MODEL_LOOP`)

The single `MODEL` variable was replaced with two separate defaults:

| Variable | Default | Used for |
|---|---|---|
| `MODEL_PLAN` | `google/gemini-3.1-pro-preview` | Stages 1 & 2 (file probe + planning) |
| `MODEL_LOOP` | `google/gemini-3-flash-preview` | Stage 3 execution loop |
| `MODEL` | *(unset)* | Overrides both if set (backward compat) |

**Rationale:** Planning benefits from the highest-capability model since it produces the
implementation strategy used for all subsequent edits. The execution loop makes many
API calls (up to 60) where latency and cost matter more; the flash model is faster and
cheaper while still capable of targeted code edits.

`call_model` now accepts an explicit `model: str` parameter. Stages 1+2 pass
`MODEL_PLAN`; stage 3 passes `MODEL_LOOP`.

---

### Makefile updated

`MODEL` removed as a top-level variable; replaced with `MODEL_PLAN`, `MODEL_LOOP`,
and `EDIT_MODE`. All three are forwarded into the container via `-e` flags.

---

## Changes (2026-02-19, iteration 3)

### Switch to Google GenAI SDK (native)

Replaced OpenRouter + `openai` package with the native `google-genai` SDK.

| Before | After |
|---|---|
| `openai` pip package | `google-genai` pip package |
| `OPENROUTER_API_KEY` env var | `GOOGLE_API_KEY` env var |
| `OpenAI(base_url="https://openrouter.ai/…")` | `genai.Client(api_key=…)` |
| `client.chat.completions.create(…)` | `client.models.generate_content(…)` |
| OpenAI message roles (`assistant`) | Google roles (`model`) |
| System message in `messages` list | `GenerateContentConfig(system_instruction=…)` |

**Message conversion** (`_build_contents`, `_extract_system`): system messages are
extracted and passed via `GenerateContentConfig`; `"assistant"` role is mapped to
`"model"` for the Google API. The rest of the agent code is unchanged.

**Model name handling**: the `google/` prefix used by OpenRouter is stripped via
`.removeprefix("google/")` before calling the native API.

**Default model names** updated to drop the `google/` prefix:
- `MODEL_PLAN` default: `gemini-3.1-pro-preview`
- `MODEL_LOOP` default: `gemini-3-flash-preview`

`Dockerfile` and `pyproject.toml` updated accordingly.

---

### Timestamped log files + logs tracked in git

Each run now writes to a uniquely named file:
```
logs/agent_YYYYMMDD_HHMMSS.log
```

- The Makefile computes `RUN_TS=$(shell date +%Y%m%d_%H%M%S)` and passes
  `LOG_FILE=/logs/agent_<RUN_TS>.log` into the container via `-e`.
- `main.py` reads `LOG_FILE` (falls back to generating its own timestamp when run
  outside Docker).
- `logs/` is now tracked in git (removed from `.gitignore`); `logs/.gitkeep`
  ensures the directory exists in fresh checkouts.
- `make logs` tails the most recent `agent_*.log` file.
- The existing `agent.log` from the first run was renamed to
  `agent_20260219_201635.log` to match the new convention.
