# -------------------------------------------------------------------------
# Lab Agent – Makefile
#
# Usage:
#   make build              – build the Docker image
#   make run                – run the agent (reads secrets from .env, logs to ./logs/)
#   make run EDIT_MODE=diff – run with search/replace diff edit mode
#   make logs               – tail the agent log
#   make clean              – remove image and log directory
#
# Secrets are read from .env (copy .env.example to .env and fill it in).
# Override individual variables on the command line, e.g.:
#   make run MODEL_LOOP=google/gemini-3.1-pro-preview EDIT_MODE=diff
# -------------------------------------------------------------------------

IMAGE_NAME ?= lab-agent
MODEL_PLAN ?= google/gemini-3.1-pro-preview
MODEL_LOOP ?= google/gemini-3-flash-preview
EDIT_MODE  ?= full
LOG_DIR    := $(PWD)/logs

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
		$(IMAGE_NAME)

logs:
	@tail -f $(LOG_DIR)/agent.log 2>/dev/null || echo "No log file found at $(LOG_DIR)/agent.log"

clean:
	-docker rmi $(IMAGE_NAME) 2>/dev/null || true
	-rm -rf $(LOG_DIR)
