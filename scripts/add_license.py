# -*- coding: utf-8 -*-
import os
import re
from datetime import datetime
from pathlib import Path

def replace_comment_header(file_path):
    """替换文件中的特定注释头"""
    # 提取文件名（包含后缀）
    file_name = os.path.basename(file_path)

    # 读取文件内容
    with open(file_path, 'r', encoding='utf-8') as f:
        content = f.read()

    # 定义要匹配的模式（使用非贪婪匹配）
    pattern = re.compile(
        r'^\s*//\s*\n\s*//\s*Created\s+by\s+(.+?)\s+on\s+(\d{4}/\d{1,2}/\d{1,2})\.\s*\n\s*//\s*',
        re.MULTILINE
    )

    # 查找匹配项
    match = pattern.search(content)
    if match:
        author = match.group(1)  # 提取作者信息
        date_str = match.group(2)  # 提取日期字符串

        # 转换日期格式（YYYY/MM/DD → YYYY-MM-DD）
        try:
            date_obj = datetime.strptime(date_str, '%Y/%m/%d')
            formatted_date = date_obj.strftime('%Y-%m-%d')
        except ValueError:
            formatted_date = date_str.replace('/', '-')

        # 构建新的注释块
        new_header = f"""/* clang-format off */
/*
 * @file {file_name}
 * @date {formatted_date}
 * @license MIT License
 *
 * Copyright (c) 2025 BinRacer <native.lab@outlook.com>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* clang-format on */
"""
        # 替换内容
        new_content = content[:match.start()] + new_header + content[match.end():]

        # 写回文件
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(new_content)
        return True
    return False

def process_directory(directory):
    """处理目录下的所有C++文件"""
    processed_files = []

    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(('.h', '.cpp')):
                file_path = os.path.join(root, file)
                if replace_comment_header(file_path):
                    processed_files.append(file_path)

    return processed_files

if __name__ == "__main__":
    base_dir = Path(__file__).parent.parent
    src_dir = base_dir / "src"
    # 设置要处理的目录（当前目录下的src文件夹）
    target_dir = src_dir

    # 执行替换操作
    modified_files = process_directory(target_dir)

    # 输出结果
    if modified_files:
        print(f"成功更新了 {len(modified_files)} 个文件:")
        # for file in modified_files:
        #     print(f"  - {file}")
    else:
        print(f"在 {target_dir} 目录中未找到匹配的C++文件")