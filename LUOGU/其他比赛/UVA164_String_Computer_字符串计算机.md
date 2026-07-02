# UVA164 - String Computer (字符串计算机)

## 题目描述

给定两个字符串，计算从一个字符串变换到另一个字符串所需的最少操作数。允许的操作包括：插入、删除、替换字符。

## 输入格式

每行两个字符串，以空格分隔。

## 输出格式

输出最少操作数。

## 样例

略。

## 提示

这是经典的编辑距离（Edit Distance）问题，也称为Levenshtein距离。

## 解题思路

### 问题分析

使用动态规划求解编辑距离。

### 核心思路

1. 定义 dp[i][j] 为 s1[0..i-1] 变换到 s2[0..j-1] 的最少操作数
2. 状态转移方程：
   - 若 s1[i-1] == s2[j-1]，dp[i][j] = dp[i-1][j-1]
   - 否则 dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])

### 算法流程

1. 初始化边界条件
2. 递推填表
3. 输出 dp[n][m]

### 复杂度分析

- 时间复杂度：O(N * M)
- 空间复杂度：O(N * M)，可优化到 O(min(N,M))

## 参考代码

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    string s1, s2;
    while (cin >> s1 >> s2) {
        int n = s1.length(), m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for (int i = 0; i <= n; i++) dp[i][0] = i;
        for (int j = 0; j <= m; j++) dp[0][j] = j;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
                }
            }
        }
        cout << dp[n][m] << "\n";
    }
    return 0;
}
```
