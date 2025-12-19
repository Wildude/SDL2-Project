#!/usr/bin/env bash
# =========================================
# Project build helper for Linux
# Creates directories, copies DLLs, then runs make
# =========================================

set -e  # exit on error (optional but recommended)

# Define directories
CORE_DIR="core"
SDL_OBJ="$CORE_DIR/SDL/obj"
BAS_OBJ="$CORE_DIR/BAS/obj"

# List of directories to create
CORE_OBJ=(
    "$SDL_OBJ"
    "$BAS_OBJ"
)

# Iterate over each directory and create it if it doesn't exist
for d in "${CORE_OBJ[@]}"; do
    if [[ ! -d "$d" ]]; then
        echo "Creating $d"
        mkdir -p "$d"
    fi
done

TEST_DIR="tests"
TEST_OBJ="$TEST_DIR/obj"
BIN_DIR="bin"
DLLS_DIR="DLLS"
BAT_DIR="batch"

# Create directories if they don't exist
for d in "$TEST_OBJ" "$BIN_DIR"; do
    if [[ ! -d "$d" ]]; then
        echo "Creating directory $d"
        mkdir -p "$d"
    fi
done

# Copy all DLLs to BIN_DIR
shopt -s nullglob
for f in "$DLLS_DIR"/*.dll; do
    echo "Copying $f to $BIN_DIR"
    cp -f "$f" "$BIN_DIR/"
done
shopt -u nullglob

echo "Copying $BAT_DIR/runbuild.bat to $BIN_DIR"
cp -f "$BAT_DIR/runbuild.bat" "$BIN_DIR/"

# Call make
echo "Running make..."
make "$@"

cd "$BIN_DIR"
