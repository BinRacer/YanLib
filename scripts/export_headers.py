# -*- coding: utf-8 -*-
import os
import re
import shutil
import zipfile
from pathlib import Path


def clean_private_section(content: str) -> str:
    """Remove private sections from header files"""
    private_section_pattern = re.compile(r'private:[\s\S]*?(?=public:)', re.DOTALL)
    cleaned_content = private_section_pattern.sub('', content)
    # Remove extra blank lines
    return re.sub(r'\n\s*\n', '\n\n', cleaned_content)


def process_header_file(source_header: Path, target_directory: Path, source_root: Path):
    """Process a single header file: clean private section and copy to include directory"""
    relative_path = source_header.relative_to(source_root)
    destination_file = target_directory / relative_path
    destination_file.parent.mkdir(parents=True, exist_ok=True)

    try:
        with open(source_header, 'r', encoding='utf-8', errors='replace') as source_file:
            header_content = source_file.read()
        cleaned_header = clean_private_section(header_content)
        with open(destination_file, 'w', encoding='utf-8') as target_file:
            target_file.write(cleaned_header)
    except UnicodeDecodeError:
        print(f"[-] Encoding error, skipping file: {source_header}")


def prepare_build_directory(build_directory: Path):
    """Prepare build directory: clean old include folder"""
    if build_directory.exists():
        shutil.rmtree(build_directory, ignore_errors=True)
    build_directory.mkdir(parents=True, exist_ok=True)


def process_all_header_files(source_directory: Path, include_directory: Path) -> int:
    """Process all header files and return processed count"""
    processed_counter = 0
    for root_path, _, file_list in os.walk(source_directory):
        for filename in file_list:
            if filename.lower().endswith(('.h', '.hpp')):
                header_file = Path(root_path) / filename
                process_header_file(header_file, include_directory, source_directory)
                processed_counter += 1
    return processed_counter


def zip_build_directory(build_directory: Path, output_zip: Path) -> int:
    """Compress build directory to ZIP file (removing build directory level)"""
    output_zip.parent.mkdir(parents=True, exist_ok=True)
    print(f"[+] Compressing {build_directory} to {output_zip}...")
    file_counter = 0

    with zipfile.ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as archive:
        for root_path, _, file_list in os.walk(build_directory):
            for filename in file_list:
                file_path = Path(root_path) / filename
                relative_in_zip = file_path.relative_to(build_directory)
                archive.write(file_path, arcname=relative_in_zip)
                file_counter += 1

    print(f"[+] Compression complete! ZIP contains {file_counter} files.")
    return file_counter


def main():
    """Main processing flow"""
    # Initialize paths
    base_directory = Path(__file__).parent.parent
    source_directory = base_directory / "src"
    include_output_dir = base_directory / "build/include"
    distribution_dir = base_directory / "dist"

    # Phase 1: Process header files
    prepare_build_directory(include_output_dir)
    processed_total = process_all_header_files(source_directory, include_output_dir)
    print(f"[+] Header processing completed! Processed files: {processed_total}")

    # Phase 2: Compress build directory
    build_root = base_directory / "build"
    final_zip_path = distribution_dir / "YanLib.zip"
    zipped_file_count = zip_build_directory(build_root, final_zip_path)
    print(f"[+] Final ZIP created with {zipped_file_count} files")


if __name__ == "__main__":
    main()
