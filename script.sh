#!/bin/bash

LOG_DIR="../log"
LOG_FILE="$LOG_DIR/app.log"

mkdir -p "$LOG_DIR"

if [ ! -f "$LOG_FILE" ]; then
    touch "$LOG_FILE"
fi
