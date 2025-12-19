#!/usr/bin/env bash
# Usage: ./clean.sh [objs|bin|test|sdl|bas|core]

set -e

# === Define directories ===
TEST_DIR="tests"
TEST_OBJ="$TEST_DIR/obj"
BIN_DIR="bin"
DLLS_DIR="DLLS"

CORE_DIR="core"
SDL_OBJ="$CORE_DIR/SDL/obj"
BAS_OBJ="$CORE_DIR/BAS/obj"
OGL_OBJ="$CORE_DIR/OGL/obj"

# List of directories to clean for "core"
CORE_OBJ_FOLDERS=(
    "$SDL_OBJ"
    "$BAS_OBJ"
)

# === Function for cleaning folders ===
clean_folders() {
    for d in "$@"; do
        if [ -d "$d" ]; then
            echo "Removing folder $d..."
            rm -rf "$d"
        else
            echo "Folder $d does not exist, skipping."
        fi
    done
}

ARG="$1"

# === Conditional handling ===
case "$ARG" in
    objs)
        echo "Removing obj folders in core and tests..."
        clean_folders "${CORE_OBJ_FOLDERS[@]}"
        clean_folders "$TEST_OBJ"
        ;;

    core)
        echo "Removing obj folders in core..."
        clean_folders "${CORE_OBJ_FOLDERS[@]}"
        ;;

    bin)
        echo "Removing bin folder..."
        clean_folders "$BIN_DIR"
        ;;

    test)
        echo "Removing test obj folder..."
        clean_folders "$TEST_OBJ"
        ;;

    sdl)
        echo "Removing SDL obj folder..."
        clean_folders "$SDL_OBJ"
        ;;

    bas)
        echo "Removing BAS obj folder..."
        clean_folders "$BAS_OBJ"
        ;;

    "")
        echo "Removing all folders..."
        clean_folders "${CORE_OBJ_FOLDERS[@]}"
        clean_folders "$TEST_OBJ"
        clean_folders "$BIN_DIR"
        ;;

    *)
        echo "Invalid argument: $ARG"
        echo "Usage: clean.sh [objs|bin|test|sdl|bas|core]"
        exit 1
        ;;
esac
