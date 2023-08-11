#!/bin/bash

# Absolute path to the installed binary
BIN_PATH="$INSTALL_DIR/bin/OnlineRamseyGame"


if [ ! -f "$BIN_PATH" ]; then
  echo "Error: Binary not found at $BIN_PATH"
  exit 1
fi

# Run the binary
"$BIN_PATH"
