# -------------------------------------------------------------------------
# Lab Agent – Docker image
#
# Includes:
#   • Python 3.12  (for the agent)
#   • Verilator    (to compile/simulate the Verilog pipeline)
#   • build tools  (make, g++, tree, perl)
# -------------------------------------------------------------------------
FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
        python3 \
        python3-pip \
        python3-venv \
        verilator \
        make \
        g++ \
        tree \
        perl \
    && rm -rf /var/lib/apt/lists/*

# Install Python dependencies system-wide (no venv needed in a container)
RUN pip3 install --break-system-packages openai

WORKDIR /app

# Copy agent code
COPY pyproject.toml ./
COPY main.py ./

# Copy the entire assignment directory so the agent can read and edit files
COPY assignment/ ./assignment/

# Log directory (expected to be bind-mounted from the host)
VOLUME ["/logs"]

ENV ASSIGNMENT_DIR=/app/assignment
ENV LOG_DIR=/logs
ENV MODEL=anthropic/claude-sonnet-4-6
ENV MAX_ITERATIONS=60

CMD ["python3", "main.py"]
