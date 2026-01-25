#!/bin/bash

# Script for creating log directory and log files.
# Creates: ../log/app.log, ../log/lexer.log, ../log/parser.log.

LOG_DIR="../log"
LOG_FILES=(
    "$LOG_DIR/app.log"
    "$LOG_DIR/lexer.log"
    "$LOG_DIR/parser.log"
)

mkdir -p "$LOG_DIR"

for file in "${LOG_FILES[@]}"; 
do
    if [ ! -f "$file" ]; 
    then
        touch "$file"
    fi
done
