import os
import shutil
import sys

def move_cpp_with_gui_include(source_folder, target_folder):
    # Ensure target folder exists
    os.makedirs(target_folder, exist_ok=True)

    # Walk through source folder recursively
    for root, dirs, files in os.walk(source_folder):
        for file in files:
            if file.endswith(".cpp"):
                file_path = os.path.join(root, file)

                try:
                    with open(file_path, "r", encoding="utf-8", errors="ignore") as f:
                        content = f.read()

                        if '#include <GUI.hpp>' in content:
                            destination_path = os.path.join(target_folder, file)

                            # Handle duplicate filenames
                            base, ext = os.path.splitext(file)
                            counter = 1
                            while os.path.exists(destination_path):
                                destination_path = os.path.join(
                                    target_folder, f"{base}_{counter}{ext}"
                                )
                                counter += 1

                            os.remove(file_path)
                            print(f"Moved: {file_path} -> {destination_path}")

                except Exception as e:
                    print(f"Error processing {file_path}: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <source_folder> <target_folder>")
        sys.exit(1)

    source = sys.argv[1]
    target = sys.argv[2]

    move_cpp_with_gui_include(source, target)