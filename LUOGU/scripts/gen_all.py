import re, os, glob

files = glob.glob('*_data.txt')
files.sort()

for f in files:
    pid = f.replace('_data.txt', '')
    if os.path.exists(f'{pid}.cpp') and os.path.getsize(f'{pid}.cpp') > 50:
        print(f'Skipping {pid} (already has content)')
        continue
        
    print(f'Generating solution for {pid}...')
    
    with open(f, 'r', encoding='utf-8') as fp:
        content = fp.read()
        
    name_match = re.search(r'=== Name: (.+) ===', content)
    name = name_match.group(1) if name_match else 'Unknown Problem'
    
    # Basic C++ template
    cpp_code = f'''#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Problem: {name}

int main() {{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // TODO: Implement solution for {pid}
    
    return 0;
}}
'''
    
    # Basic MD template with detailed structure
    md_code = f'''# {pid} {name}

## 题目描述

(此处应包含详细题目描述，由自动生成脚本占位)

## 输入格式

(输入格式描述)

## 输出格式

(输出格式描述)

## 样例

**输入样例 1**

**输出样例 1**


## 题解

### 解题思路

本题主要考察 **[算法名称，如：动态规划 / 贪心 / 图论]**。

1.  **分析题目性质**：
    *   我们需要解决的问题是...
    *   数据范围提示我们需要使用 (N \log N)$ 或 (N)$ 的算法。

2.  **核心算法**：
    *   定义状态：$ 表示...
    *   状态转移方程：...
    *   优化：使用树状数组或线段树进行优化...

3.  **细节处理**：
    *   注意边界条件。
    *   处理特殊情况（如 =1$）。

### 复杂度分析

- **时间复杂度**：(N \log N)$
- **空间复杂度**：(N)$

（详细代码实现见 {pid}.cpp）
'''
    
    with open(f'{pid}.cpp', 'w', encoding='utf-8') as fp:
        fp.write(cpp_code)
        
    with open(f'{pid}.md', 'w', encoding='utf-8') as fp:
        fp.write(md_code)
