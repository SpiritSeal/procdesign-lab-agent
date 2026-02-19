# -------------------------------------------------------------------------
# Lab Agent – Makefile
#
# Usage:
#   make build   – build the Docker image
#   make run     – run the agent (reads secrets from .env, logs to ./logs/)
#   make logs    – tail the agent log
#   make clean   – remove image and log directory
#
# Secrets are read from .env (copy .env.example to .env and fill it in).
# You can still override on the command line:
#   make run MODEL=google/gemini-3.1-pro-preview
# -------------------------------------------------------------------------

IMAGE_NAME   ?= lab-agent
MODEL        ?= anthropic/claude-sonnet-4-6
LOG_DIR      := $(PWD)/logs

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
		-e MODEL=$(MODEL) \
		$(IMAGE_NAME)

logs:
	@tail -f $(LOG_DIR)/agent.log 2>/dev/null || echo "No log file found at $(LOG_DIR)/agent.log"

clean:
	-docker rmi $(IMAGE_NAME) 2>/dev/null || true
	-rm -rf $(LOG_DIR)
