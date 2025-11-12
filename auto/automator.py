
# automator.py

import argparse
import shutil
from pathlib import Path
import sys


def copy_hpp_to_cpp(src: Path, dst: Path, recursive: bool = True, dry_run: bool = False, overwrite: bool = True):
    if not src.is_dir():
        raise NotADirectoryError(f"Source is not a directory: {src}")
    dst.mkdir(parents=True, exist_ok=True)

    iterator = src.rglob("*") if recursive else src.glob("*")
    for src_path in iterator:
        if not src_path.is_file():
            continue
        if src_path.suffix.lower() != ".hpp":
            continue

        rel = src_path.relative_to(src)
        dest_path = (dst / rel).with_suffix(".cpp")
        dest_path.parent.mkdir(parents=True, exist_ok=True)

        if dest_path.exists() and not overwrite:
            print(f"Skipping (exists): {dest_path}")
            continue

        print(f"Copying: {src_path} -> {dest_path}")
        if not dry_run:
            shutil.copy2(src_path, dest_path)

def parse_args():
    p = argparse.ArgumentParser(description="Copy .hpp files to another directory as .cpp files.")
    p.add_argument("src", type=Path, help="Source directory to scan for .hpp files")
    p.add_argument("dst", type=Path, help="Destination directory to write .cpp files")
    p.add_argument("--no-recursive", action="store_true", help="Do not recurse into subdirectories")
    p.add_argument("--dry-run", action="store_true", help="Show what would be done without copying")
    p.add_argument("--no-overwrite", action="store_true", help="Do not overwrite existing files in destination")
    return p.parse_args()

def main():
    args = parse_args()
    try:
        copy_hpp_to_cpp(
            src=args.src,
            dst=args.dst,
            recursive=not args.no_recursive,
            dry_run=args.dry_run,
            overwrite=not args.no_overwrite,
        )
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

if __name__ == "__main__":
    main()