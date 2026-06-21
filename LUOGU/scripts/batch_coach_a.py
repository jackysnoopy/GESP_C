#!/usr/bin/env python3
"""
批量获取张老师(Coach-A)的七级难度3题目信息
"""

import os
import re
import sys
import json
import time
import html
import urllib.request

BASE_DIR = "/Users/jackychen/workspace/code/c++/LUOGU"

def load_problems():
    problems = []
    with open(os.path.join(BASE_DIR, "assignment.md"), "r") as f:
        content = f.read()
    match = re.search(r'=== 张老师 \(Coach-A\) 负责题目 ===(.*?)(?:===|$)', content, re.DOTALL)
    if not match:
        return []
    section = match.group(1)
    for line in section.strip().split('\n'):
        line = line.strip()
        if not line:
            continue
        parts = line.split('|')
        if len(parts) >= 2 and parts[0].strip().startswith('P'):
            pid = parts[0].strip()
            name = parts[1].strip() if len(parts) > 1 else ""
            problems.append((pid, name))
    return problems

def get_c3vk():
    url = "https://www.luogu.com.cn/"
    req = urllib.request.Request(url, headers={
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36'
    })
    try:
        resp = urllib.request.urlopen(req, timeout=10)
        cookies = resp.headers.get_all('Set-Cookie') or []
        for c in cookies:
            m = re.search(r'C3VK=([^;]+)', c)
            if m:
                return m.group(1)
    except Exception as e:
        print(f"获取C3VK失败: {e}", file=sys.stderr)
    return None

def fetch_problem(pid, c3vk):
    url = f"https://www.luogu.com.cn/problem/{pid}"
    req = urllib.request.Request(url, headers={
        'User-Agent': 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36',
        'Cookie': f'C3VK={c3vk}'
    })
    try:
        resp = urllib.request.urlopen(req, timeout=15)
        html_content = resp.read().decode('utf-8')
        m = re.search(r'<script id="lentille-context"[^>]*>(.*?)</script>', html_content, re.DOTALL)
        if not m:
            return None
        data = json.loads(m.group(1))
        problem = data.get('data', {}).get('problem', {})
        return problem
    except Exception as e:
        print(f"  错误: {pid} 请求失败: {e}", file=sys.stderr)
        return None

def format_problem_info(problem):
    pid = problem.get('pid', '')
    title = problem.get('title', '')
    difficulty = problem.get('difficulty', 0)
    description = problem.get('description', '')
    input_format = problem.get('inputFormat', '')
    output_format = problem.get('outputFormat', '')
    samples = problem.get('samples', [])
    hint = problem.get('hint', '')
    limits = problem.get('limits', {})
    
    info = f"=== PID: {pid} ===\n"
    info += f"=== Name: {title} ===\n"
    info += f"=== Difficulty: {difficulty} ===\n"
    info += f"=== Description ===\n{html.unescape(description)}\n"
    info += f"=== Input ===\n{html.unescape(input_format)}\n"
    info += f"=== Output ===\n{html.unescape(output_format)}\n"
    info += "=== Samples ===\n"
    for i, sample in enumerate(samples):
        inp = sample.get('input', '')
        out = sample.get('output', '')
        info += f"Sample {i+1}:\nInput:\n{inp}\nOutput:\n{out}\n\n"
    info += f"=== Hint ===\n{html.unescape(hint)}\n"
    info += f"=== Limits ===\n{json.dumps(limits, ensure_ascii=False)}\n"
    return info

def main():
    problems = load_problems()
    print(f"总共 {len(problems)} 道题目")
    
    output_dir = os.path.join(BASE_DIR, "七级", "难度3")
    remaining = [(pid, name) for pid, name in problems if not os.path.exists(os.path.join(output_dir, f"{pid}.cpp"))]
    print(f"已完成 {len(problems) - len(remaining)} 道，剩余 {len(remaining)} 道")
    
    if not remaining:
        print("所有题目已完成！")
        return
    
    c3vk = get_c3vk()
    if not c3vk:
        print("无法获取C3VK", file=sys.stderr)
        return
    print(f"C3VK获取成功")
    
    info_dir = "/tmp/luogu_infos"
    os.makedirs(info_dir, exist_ok=True)
    
    count = 0
    for i, (pid, name) in enumerate(remaining):
        print(f"[{i+1}/{len(remaining)}] {pid} - {name}")
        
        if count % 10 == 0 and count > 0:
            new_c3vk = get_c3vk()
            if new_c3vk:
                c3vk = new_c3vk
        
        problem = fetch_problem(pid, c3vk)
        if not problem:
            print(f"  跳过 {pid}")
            continue
        
        info = format_problem_info(problem)
        info_path = os.path.join(info_dir, f"{pid}_info.txt")
        with open(info_path, "w") as f:
            f.write(info)
        
        print(f"  OK: {problem.get('title', '未知')}")
        count += 1
        time.sleep(0.5)
    
    print(f"\n共获取 {count} 道题目信息到 {info_dir}")

if __name__ == "__main__":
    main()
