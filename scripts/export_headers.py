# -*- coding: utf-8 -*-
import os
import re
import shutil
from pathlib import Path


def clean_private_section(content: str) -> str:
    """使用正则表达式清除private到public之间的所有内容（含private标签）"""
    # 匹配private:到public:的区域（包含private自身）
    pattern = re.compile(
        r'private:[\s\S]*?(?=public:)',  # 正向预查确保保留public:
        re.DOTALL
    )
    # 替换为仅保留public:并重置缩进
    cleaned = pattern.sub('', content)
    # 合并连续空行至单空行
    return re.sub(r'\n\s*\n', '\n\n', cleaned)


def process_header(src_file: Path, include_dir: Path):
    """处理单个头文件并生成到include目录"""
    # 生成目标路径（保留src的目录结构）
    rel_path = src_file.relative_to(src_dir)
    target_file = include_dir / rel_path

    # 创建目标目录结构（支持嵌套目录）
    target_file.parent.mkdir(parents=True, exist_ok=True)

    # 读取并处理内容
    try:
        with open(src_file, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()

        # 执行清理操作
        cleaned_content = clean_private_section(content)

        # 写入新文件（保留原文件编码）
        with open(target_file, 'w', encoding='utf-8') as f:
            f.write(cleaned_content)
    except UnicodeDecodeError:
        print(f"⚠️  编码错误跳过文件：{src_file}")


if __name__ == "__main__":
    base_dir = Path(__file__).parent.parent
    src_dir = base_dir / "src"
    include_dir = base_dir / "build/include"

    # 清除并重建include目录（支持嵌套结构）
    if include_dir.exists():
        shutil.rmtree(include_dir, ignore_errors=True)
    include_dir.mkdir(parents=True, exist_ok=True)

    # 遍历src目录处理文件
    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.lower().endswith(('.h', '.hpp')):
                src_file = Path(root) / file
                process_header(src_file, include_dir)

    print(f"✅ 处理完成！生成文件数：{sum(1 for _ in include_dir.glob('**/*.h*'))}")
