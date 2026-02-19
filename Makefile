# -------------------------------------------------------------------------
# Lab Agent – Makefile
#
# Usage:
#   make build              – build the Docker image
#   make run                – run the agent (reads .env, logs to ./logs/)
#   make run EDIT_MODE=diff – run with search/replace diff edit mode
#   make logs               – tail the most recent run log
#   make clean              – remove image and log directory
#
# Secrets are read from .env (copy .env.example to .env and fill it in).
# Override individual variables on the command line, e.g.:
#   make run MODEL_LOOP=gemini-3.1-pro-preview EDIT_MODE=diff
# -------------------------------------------------------------------------

IMAGE_NAME ?= lab-agent
MODEL_PLAN ?= gemini-3.1-pro-preview
MODEL_LOOP ?= gemini-3-flash-preview
EDIT_MODE  ?= full
LOG_DIR    := $(PWD)/logs

# Unique log file name based on wall-clock start time
RUN_TS     := $(shell date +%Y%m%d_%H%M%S)
LOG_FILE   := $(LOG_DIR)/agent_$(RUN_TS).log

# Load .env if it exists (silently skip if absent)
-include .env
export

.PHONY: build run logs clean

build:
	docker build -t $(IMAGE_NAME) .

run: build
	@mkdir -p $(LOG_DIR)
	docker run --rm \
		-v $(LOG_DIR):/logs \
		--env-file .env \
		-e MODEL_PLAN=$(MODEL_PLAN) \
		-e MODEL_LOOP=$(MODEL_LOOP) \
		-e EDIT_MODE=$(EDIT_MODE) \
		-e LOG_FILE=/logs/agent_$(RUN_TS).log \
		$(IMAGE_NAME)

logs:
	@latest=$$(ls -t $(LOG_DIR)/agent_*.log 2>/dev/null | head -1); \
	if [ -z "$$latest" ]; then \
		echo "No log files found in $(LOG_DIR)"; \
	else \
		echo "Tailing $$latest"; \
		tail -f "$$latest"; \
	fi

clean:
	-docker rmi $(IMAGE_NAME) 2>/dev/null || true
	-rm -rf $(LOG_DIR)
