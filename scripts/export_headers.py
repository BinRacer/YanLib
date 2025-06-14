# -*- coding: utf-8 -*-
import os
import re
import shutil
from pathlib import Path


def clean_private_section(content: str) -> str:
    """Remove all content between private: and public: using regex (including the private: label)"""
    # Match the region from private: to public: (including private: itself)
    pattern = re.compile(
        r'private:[\s\S]*?(?=public:)',  # Positive lookahead ensures public: is preserved
        re.DOTALL
    )
    # Replace matched content with empty string
    cleaned = pattern.sub('', content)
    # Collapse consecutive blank lines into a single blank line
    return re.sub(r'\n\s*\n', '\n\n', cleaned)


def process_header(src_file: Path, include_dir: Path):
    """Process a single header file and output it to the include directory"""
    # Generate target path (preserving src directory structure)
    rel_path = src_file.relative_to(src_dir)
    target_file = include_dir / rel_path

    # Create target directory structure (supports nested directories)
    target_file.parent.mkdir(parents=True, exist_ok=True)

    # Read and process file content
    try:
        with open(src_file, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()

        # Perform cleanup operation
        cleaned_content = clean_private_section(content)

        # Write to new file (preserves original encoding)
        with open(target_file, 'w', encoding='utf-8') as f:
            f.write(cleaned_content)
    except UnicodeDecodeError:
        print(f"⚠️  Encoding error, skipping file: {src_file}")


if __name__ == "__main__":
    base_dir = Path(__file__).parent.parent
    src_dir = base_dir / "src"
    include_dir = base_dir / "build/include"

    # Clear and recreate include directory (supports nested structure)
    if include_dir.exists():
        shutil.rmtree(include_dir, ignore_errors=True)
    include_dir.mkdir(parents=True, exist_ok=True)

    # Process all files in src directory
    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.lower().endswith(('.h', '.hpp')):
                src_file = Path(root) / file
                process_header(src_file, include_dir)

    print(f"✅ Processing completed! File count generated: {sum(1 for _ in include_dir.glob('**/*.h*'))}")
