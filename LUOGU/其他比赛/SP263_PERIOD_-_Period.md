# PERIOD - Period

## 题目描述

给定一个字符串 s，对于每个位置 i（2 ≤ i ≤ n），找出最长的前缀长度 p，使得 s[1..i] 可以由长度为 i/p 的子串重复 p 次构成。若 p > 1 则输出 i 和 p。

## 输入格式

- 多组测试数据，每组第一行一个整数 n
- 接下来一行字符串 s（长度为 n）

## 输出格式

对于每组数据，输出 "Test case #" 加上组号，然后每行输出 i 和 p

## 样例

```
输入：
10
aababcabcab
6
abcabc

输出：
Test case #1
6 2
9 3

Test case #2
6 2
```

## 提示

- 使用 KMP 算法的 failure 函数（next 数组）
- 对于位置 i，若 i % (i - nxt[i]) == 0 且 i / (i - nxt[i]) > 1，则存在周期

## 解题思路

### 问题分析

需要找到字符串每个前缀的最小周期，判断是否存在重复模式。

### 核心思路

利用 KMP 的 failure 函数（next 数组）。对于位置 i，最小周期长度为 p = i - nxt[i]。若 i % p == 0 且 i/p > 1，则该前缀由长度为 p 的子串重复 i/p 次构成。

### 算法流程

1. 计算字符串的 KMP failure 函数 nxt[]
2. 对于每个位置 i（从 2 到 n）：
   - 计算最小周期 p = i - nxt[i]
   - 若 i % p == 0 且 i/p > 1，输出 i 和 i/p

### 复杂度分析

- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T; cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        int n; string s;
        cin >> n >> s;
        
        vector<int> nxt(n+1, 0);
        for (int i = 2, j = 0; i <= n; i++) {
            while (j && s[i-1] != s[j]) j = nxt[j];
            if (s[i-1] == s[j]) j++;
            nxt[i] = j;
        }
        
        cout << "Test case #" << cas << "\n";
        for (int i = 2; i <= n; i++) {
            int p = i - nxt[i];
            if (i % p == 0 && i / p > 1)
                cout << i << " " << i / p << "\n";
        }
        cout << "\n";
    }
    return 0;
}
```
