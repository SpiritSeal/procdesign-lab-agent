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
RUN pip3 install --break-system-packages google-genai

WORKDIR /app

# Copy agent code
COPY pyproject.toml ./
COPY main.py ./

# Copy the assignment as the initial working state
COPY assignment/ ./assignment/

# Output directory – bind-mounted from the host at runtime.
# Contains agent.log, costs.json, and a copy of the final assignment files.
VOLUME ["/output"]

ENV ASSIGNMENT_DIR=/app/assignment
ENV OUTPUT_DIR=/output
ENV MODEL_PLAN=gemini-3.1-pro-preview
ENV MODEL_LOOP=gemini-3-flash-preview
ENV EDIT_MODE=full
ENV MAX_ITERATIONS=60

CMD ["python3", "main.py"]
