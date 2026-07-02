# UVA129 - Krypton Factor (氪因子)

## 题目描述

给定一个长度 n 和一个序号 k，找到第 k 个"困难"序列。

序列由字母 A、B、C 组成，一个序列是"困难"的，当且仅当它不包含两个相邻的相同子序列（长度相同）。

例如：
- "AABBB" 是困难的，因为 "AA" 和 "BB" 不是相邻的相同子序列
- "ABBA" 不是困难的，因为 "AB" 和 "BA" 虽然不相同
- "ABAB" 不是困难的，因为 "AB" 和 "AB" 是相邻的相同子序列

序列按字典序排列，找到第 k 个困难序列。

## 输入格式

- 每行两个整数 n 和 k
- n 表示序列长度（1 ≤ n ≤ 44）
- k 表示要找第几个困难序列
- 当 n = 0 且 k = 0 时输入结束

## 输出格式

- 输出第 k 个困难序列
- 每 4 个字符输出一个空格
- 每个输出后空一行

## 样例

输入：
```
7 3
7 4
0 0
```

输出：
```
ABABAAC
ABACAAB
```

## 解题思路

### 问题分析

这是一个经典的回溯搜索问题。需要按字典序生成所有困难序列，直到找到第 k 个。

关键在于如何判断一个序列是否是"困难"的：
- 在每次添加新字符后，检查是否存在相邻的相同子序列
- 只需要检查新添加的字符是否导致了重复

### 核心思路

1. 使用回溯法（DFS）按字典序生成序列
2. 每次添加字符 A、B 或 C
3. 每次添加后检查是否仍然是困难序列
4. 维护计数器，找到第 k 个时输出

### 判断困难序列的方法

检查新添加的字符是否与前面的子序列构成重复：
- 对于长度 l = 1, 2, 3, ...，检查序列末尾的 2l 个字符
- 如果末尾 l 个字符与前 l 个字符完全相同，则不是困难序列

### 算法流程

1. 读取 n 和 k
2. 初始化计数器 cnt = 0
3. 从空序列开始 DFS：
   - 尝试添加 'A'、'B'、'C'
   - 检查添加后是否仍是困难序列
   - 如果是，继续递归
   - 如果序列长度达到 n，cnt++
   - 当 cnt == k 时，输出结果并返回

### 复杂度分析

- 时间复杂度：O(3^n * n)，最坏情况需要检查所有可能的序列
- 空间复杂度：O(n)，递归栈深度

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <functional>
using namespace std;

int n, k;
int cnt;

bool check(const string& s, int len) {
    int slen = s.size();
    if (slen < 2 * len) return true;
    for (int i = slen - 2 * len; i < slen - len; i++) {
        bool ok = false;
        for (int j = 0; j < len; j++) {
            if (s[i + j] != s[i + len + j]) {
                ok = true;
                break;
            }
        }
        if (!ok) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    function<void(string&, int)> dfs = [&](string& s, int depth) {
        if (cnt >= k) return;
        if (depth == n) {
            cnt++;
            if (cnt == k) {
                for (int i = 0; i < n; i++) {
                    if (i > 0 && i % 4 == 0) cout << " ";
                    cout << s[i];
                }
                cout << "\n";
            }
            return;
        }
        for (char c = 'A'; c <= 'C'; c++) {
            s.push_back(c);
            if (check(s, 1) && check(s, 2)) {
                dfs(s, depth + 1);
            }
            s.pop_back();
            if (cnt >= k) return;
        }
    };
    
    while (cin >> n >> k && (n != 0 || k != 0)) {
        cnt = 0;
        string s;
        dfs(s, 0);
    }
    
    return 0;
}
```
