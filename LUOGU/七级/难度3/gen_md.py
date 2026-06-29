import os
import re
import json

def parse_data(data_file):
    with open(data_file, 'r', encoding='utf-8') as f:
        content = f.read()
    # Extract name
    m = re.search(r'=== Name: (.+?) ===', content)
    name = m.group(1).strip() if m else ''
    # Extract description
    m = re.search(r'=== Description ===\n(.*?)(?=\n=== Input ===)', content, re.DOTALL)
    description = m.group(1).strip() if m else ''
    # Extract input format
    m = re.search(r'=== Input ===\n(.*?)(?=\n=== Output ===)', content, re.DOTALL)
    input_format = m.group(1).strip() if m else ''
    # Extract output format
    m = re.search(r'=== Output ===\n(.*?)(?=\n=== Hint ===)', content, re.DOTALL)
    output_format = m.group(1).strip() if m else ''
    # Extract hint
    m = re.search(r'=== Hint ===\n(.*?)(?=\n=== Samples ===)', content, re.DOTALL)
    hint = m.group(1).strip() if m else ''
    # Extract samples
    samples = []
    sample_pattern = re.compile(r'--- Sample (\d+) ---\nInput:\n(.*?)\nOutput:\n(.*?)(?=\n--- Sample|\n=== Limits ===)', re.DOTALL)
    for sm in sample_pattern.finditer(content):
        inp = sm.group(2).strip()
        out = sm.group(3).strip()
        samples.append((inp, out))
    return name, description, input_format, output_format, hint, samples

def generate_md(pid, name, description, input_format, output_format, hint, samples, cpp_code):
    lines = []
    lines.append(f'# {name}')
    lines.append('')
    lines.append('## 题目描述')
    lines.append('')
    lines.append(description)
    lines.append('')
    lines.append('## 输入格式')
    lines.append('')
    lines.append(input_format)
    lines.append('')
    lines.append('## 输出格式')
    lines.append('')
    lines.append(output_format)
    lines.append('')
    lines.append('## 样例')
    lines.append('')
    for i, (inp, out) in enumerate(samples, 1):
        lines.append(f'### 样例输入 {i}')
        lines.append('```')
        lines.append(inp)
        lines.append('```')
        lines.append('')
        lines.append(f'### 样例输出 {i}')
        lines.append('```')
        lines.append(out)
        lines.append('```')
        lines.append('')
    lines.append('## 提示')
    lines.append('')
    lines.append(hint)
    lines.append('')
    lines.append('## 解题思路')
    lines.append('')
    lines.append('### 问题分析')
    lines.append('待补充')
    lines.append('')
    lines.append('### 核心思路')
    lines.append('待补充')
    lines.append('')
    lines.append('### 算法流程')
    lines.append('待补充')
    lines.append('')
    lines.append('### 复杂度分析')
    lines.append('待补充')
    lines.append('')
    lines.append('## 参考代码')
    lines.append('')
    lines.append('```cpp')
    lines.append(cpp_code.strip())
    lines.append('```')
    return '\n'.join(lines)

def main():
    import sys
    pids = sys.argv[1:]
    for pid in pids:
        data_file = f'{pid}_data.txt'
        cpp_file = f'{pid}.cpp'
        if not os.path.exists(data_file):
            print(f'Skipping {pid}: data file not found')
            continue
        if not os.path.exists(cpp_file):
            print(f'Skipping {pid}: cpp file not found')
            continue
        name, desc, inp, out, hint, samples = parse_data(data_file)
        with open(cpp_file, 'r', encoding='utf-8') as f:
            cpp_code = f.read()
        md_content = generate_md(pid, name, desc, inp, out, hint, samples, cpp_code)
        # Generate filename: {pid}_{clean_name}.md
        clean = re.sub(r'[^\w\u4e00-\u9fff\-]', '_', name)
        clean = re.sub(r'_+', '_', clean).strip('_')
        md_filename = f'{pid}_{clean}.md'
        with open(md_filename, 'w', encoding='utf-8') as f:
            f.write(md_content)
        print(f'Generated {md_filename}')

if __name__ == '__main__':
    main()
