# -*- coding: utf-8 -*-
import os
import shutil
import zipfile
from pathlib import Path


def process_header_file(source_header: Path, target_directory: Path, source_root: Path):
    """Copy header files while preserving directory structure"""
    relative_path = source_header.relative_to(source_root)
    destination_file = target_directory / relative_path

    # Ensure target directory exists
    destination_file.parent.mkdir(parents=True, exist_ok=True)

    try:
        # Direct binary copy preserving file metadata
        shutil.copy2(source_header, destination_file)
    except OSError as e:
        print(f"[-] File copy error ({e.strerror}): {source_header}")


def prepare_build_directory(build_directory: Path):
    """Clean and recreate build directory"""
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
    """Compress build directory to ZIP file (flattening directory structure)"""
    output_zip.parent.mkdir(parents=True, exist_ok=True)
    print(f"[+] Compressing directory: {build_directory}")

    file_counter = 0
    try:
        with zipfile.ZipFile(output_zip, 'w', zipfile.ZIP_DEFLATED) as archive:
            for root_path, _, file_list in os.walk(build_directory):
                for filename in file_list:
                    file_path = Path(root_path) / filename
                    # Use relative path to maintain directory structure
                    relative_in_zip = file_path.relative_to(build_directory)
                    archive.write(file_path, arcname=relative_in_zip)
                    file_counter += 1
    except zipfile.BadZipFile as e:
        print(f"[-] ZIP creation failed: {e}")
        return 0

    print(f"[+] Compression complete! ZIP contains {file_counter} files.")
    return file_counter


def main():
    """Main processing flow with simplified header handling"""
    # Initialize paths
    base_directory = Path(__file__).parent.parent
    source_directory = base_directory / "src"
    include_output_dir = base_directory / "build/include"
    distribution_dir = base_directory / "dist"

    # Phase 1: Copy header files
    prepare_build_directory(include_output_dir)
    processed_total = process_all_header_files(source_directory, include_output_dir)
    print(f"[+] Header files copied: {processed_total} files processed")

    # Phase 2: Create distribution package
    build_root = base_directory / "build"
    final_zip_path = distribution_dir / "YanLib.zip"
    zipped_file_count = zip_build_directory(build_root, final_zip_path)
    print(f"[+] Distribution package created: {final_zip_path}")


if __name__ == "__main__":
    main()