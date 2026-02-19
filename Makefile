# -------------------------------------------------------------------------
# Lab Agent – Makefile
#
# Usage:
#   make build              – build the Docker image
#   make run                – run the agent; output in ./logs/run_TIMESTAMP/
#   make run EDIT_MODE=diff – run with search/replace diff edit mode
#   make logs               – tail the most recent agent.log
#   make clean              – remove image and log directory
#
# Secrets are read from .env (copy .env.example to .env and fill it in).
# Override individual variables on the command line, e.g.:
#   make run MODEL_LOOP=gemini-3.1-pro-preview EDIT_MODE=diff
#
# Each run produces:
#   logs/run_TIMESTAMP/
#     agent.log       – full agent log
#     costs.json      – token usage and cost breakdown
#     assignment/     – final state of all edited files
# -------------------------------------------------------------------------

IMAGE_NAME ?= lab-agent
MODEL_PLAN ?= gemini-3.1-pro-preview
MODEL_LOOP ?= gemini-3-flash-preview
EDIT_MODE  ?= full
LOG_DIR    := $(PWD)/logs

# Each run gets its own output directory
RUN_TS     := $(shell date +%Y%m%d_%H%M%S)
RUN_DIR    := $(LOG_DIR)/run_$(RUN_TS)

# Load .env if it exists (silently skip if absent)
-include .env
export

.PHONY: build run logs clean

build:
	docker build -t $(IMAGE_NAME) .

run: build
	@mkdir -p $(RUN_DIR)
	docker run --rm \
		-v $(RUN_DIR):/output \
		--env-file .env \
		-e MODEL_PLAN=$(MODEL_PLAN) \
		-e MODEL_LOOP=$(MODEL_LOOP) \
		-e EDIT_MODE=$(EDIT_MODE) \
		$(IMAGE_NAME)

logs:
	@latest=$$(ls -t $(LOG_DIR)/run_*/agent.log 2>/dev/null | head -1); \
	if [ -z "$$latest" ]; then \
		echo "No log files found under $(LOG_DIR)/run_*/"; \
	else \
		echo "Tailing $$latest"; \
		tail -f "$$latest"; \
	fi

clean:
	-docker rmi $(IMAGE_NAME) 2>/dev/null || true
	-rm -rf $(LOG_DIR)
