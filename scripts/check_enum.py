# -*- coding: utf-8 -*-
import os
import re
from collections import defaultdict
from pathlib import Path

def find_enums_in_file(file_path):
    """Parse a single header file and extract all enum type names"""
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except Exception as e:
        print(f"Error reading {file_path}: {str(e)}")
        return set()

    # Enum matching patterns
    patterns = [
        re.compile(r'enum\s+class\s+(\w+)\s*(?::\s*\w+\s*)?\{[\s\S]*?\}(?=\s*;)', re.DOTALL),  # enum class
        re.compile(r'enum\s+(\w+)\s*\{[\s\S]*?\}(?=\s*;)', re.DOTALL),  # standard enum
        re.compile(r'typedef\s+enum\s*(\w+)?\s*\{[\s\S]*?\}\s*(\w+)\s*;', re.DOTALL)  # typedef enum
    ]

    found_enums = set()

    # Process first two patterns
    for pattern in patterns[:2]:
        for match in pattern.finditer(content):
            if match.group(1):
                found_enums.add(match.group(1))

    # Process typedef pattern
    for match in patterns[2].finditer(content):
        enum_name = match.group(2) or match.group(1)
        if enum_name:
            found_enums.add(enum_name)

    return found_enums

def scan_src_directory(src_dir):
    """Traverse directory tree to collect enum information and build mapping relations"""
    file_enums = {}
    enum_files = defaultdict(set)

    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.endswith(('.h', '.hpp')):
                file_path = os.path.join(root, file)
                rel_path = os.path.relpath(file_path, src_dir)
                enums = find_enums_in_file(file_path)
                if enums:
                    file_enums[rel_path] = enums
                    for enum_name in enums:
                        enum_files[enum_name].add(rel_path)

    return file_enums, enum_files

def generate_shared_info(file_enums, enum_files):
    """Generate mapping of files sharing enums"""
    shared_relations = defaultdict(set)

    for file, enums in file_enums.items():
        for enum_name in enums:
            # Get all files containing same enum (excluding self)
            related_files = enum_files[enum_name] - {file}
            for related_file in related_files:
                shared_relations[file].add(related_file)

    return shared_relations

def print_results(file_enums, shared_relations):
    """Format and print results"""
    for file, enums in sorted(file_enums.items()):
        print(f"{file}:")
        print("  - Enum Definitions:")
        for enum_name in sorted(enums):
            print(f"    * {enum_name}")

        if shared_relations[file]:
            print("  - Header Files Sharing Enums:")
            for related_file in sorted(shared_relations[file]):
                # Identify shared enum names
                shared_enums = sorted(file_enums[file] & file_enums[related_file])
                enum_list = ", ".join(shared_enums)
                print(f"    * {related_file} (Shared Enums: {enum_list})")
        else:
            print("  - No Header Files Share Enums")
        print()  # empty line separator

if __name__ == "__main__":
    base_directory = Path(__file__).parent.parent
    src_directory = base_directory / "src"

    if not os.path.exists(src_directory):
        print(f"Error: Directory '{src_directory}' does not exist!")
        exit(1)

    file_enums, enum_files = scan_src_directory(src_directory)
    shared_relations = generate_shared_info(file_enums, enum_files)
    print_results(file_enums, shared_relations)