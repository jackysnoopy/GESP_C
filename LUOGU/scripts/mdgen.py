# -*- coding: utf-8 -*-
"""洛谷题解 .md 生成器库：解析 _data.txt + 组装标准 md。"""
import os, re

def _dir():
    return os.environ.get('MDGEN_DIR', '.')

def parse_data(pid):
    """解析 {pid}_data.txt。
    行内段：=== Name: 值 ===   (PID/Name/Difficulty)
    块段：=== Description ===\n<内容>  (Background/Description/Input/Output/Hint/Samples/Limits)"""
    path = os.path.join(_dir(), f'{pid}_data.txt')
    with open(path, encoding='utf-8') as f:
        raw = f.read()
    tokens = re.split(r'^=== (.+?) ===\s*$', raw, flags=re.MULTILINE)
    sec = {}
    i = 1
    while i < len(tokens):
        header = tokens[i].strip()
        content = tokens[i+1].strip('\n') if i+1 < len(tokens) else ''
        if ':' in header:
            key, val = header.split(':', 1)
            sec[key.strip()] = val.strip()
        else:
            sec[header] = content.strip()
        i += 2
    return sec

def read_cpp(pid):
    path = os.path.join(_dir(), f'{pid}.cpp')
    with open(path, encoding='utf-8') as f:
        return f.read().rstrip('\n')

def clean_title(name):
    m = re.match(r'^(\[.+?\]\s*)?(.+)$', name)
    title = m.group(2).strip() if m else name
    clean = re.sub(r'[^\w\u4e00-\u9fff\-]', '_', title)
    clean = re.sub(r'_+', '_', clean).strip('_')
    return clean or 'solution'

def build_md(pid, solution_md):
    sec = parse_data(pid)
    name = sec.get('Name', pid).strip()
    desc = sec.get('Description', '').strip()
    inp = sec.get('Input', '').strip()
    out = sec.get('Output', '').strip()
    hint = sec.get('Hint', '').strip()
    samples = sec.get('Samples', '').strip()
    cpp = read_cpp(pid)
    md = []
    md.append(f'# {name}\n')
    md.append('## 题目描述\n')
    md.append((desc + '\n') if desc else '(无)\n')
    md.append('## 输入格式\n')
    md.append((inp + '\n') if inp else '(无)\n')
    md.append('## 输出格式\n')
    md.append((out + '\n') if out else '(无)\n')
    md.append('## 样例\n')
    md.append((samples + '\n') if samples else '(无)\n')
    md.append('## 提示\n')
    md.append((hint + '\n') if hint else '(无)\n')
    md.append('## 解题思路\n')
    md.append(solution_md.rstrip('\n') + '\n')
    md.append('## 参考代码\n')
    md.append('```cpp\n')
    md.append(cpp + '\n')
    md.append('```\n')
    return '\n'.join(md)

def md_filename(pid):
    sec = parse_data(pid)
    name = sec.get('Name', pid).strip()
    return f'{pid}_{clean_title(name)}.md'

def write_md(pid, solution_md):
    md = build_md(pid, solution_md)
    fname = md_filename(pid)
    path = os.path.join(_dir(), fname)
    with open(path, 'w', encoding='utf-8') as f:
        f.write(md)
    return fname
