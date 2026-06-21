# [GCJ 2017 Qualification] Oversized Pancake Flipper

## 题目描述

你有一个由\`+\`和\`-\`组成的字符串，长度为N。每次你可以选择一个长度为K的子串，并翻转其中的所有字符（\`+\`变\`-\`，\`-\`变\`+\`）。你的目标是让整个字符串全部变成\`+\`。

如果无法完成目标，输出"IMPOSSIBLE"；否则输出最小翻转次数。

## 输入格式

第一行：N K
第二行：字符串 S

## 输出格式

最小翻转次数或"IMPOSSIBLE"

## 提示

数据范围：1 ≤ N ≤ 1000, 1 ≤ K ≤ N

## 解题思路

### 问题分析
- 给定一个由\`+\`和\`-\`组成的字符串
- 每次操作：选择长度为K的子串，翻转所有字符
- 目标：让整个字符串全部变成\`+\`
- 求最小操作次数

### 核心思路
**贪心策略**：
1. 从左到右扫描字符串
2. 遇到第一个\`-\`时，必须翻转从这个位置开始的K长度子串
3. 继续扫描，翻转所有需要的位置
4. 最后检查是否全为\`+\`

### 算法流程
1. 读入N, K和字符串S
2. 从左到右扫描，遇到\`-\`就翻转K长度
3. 统计翻转次数
4. 检查最终字符串，如果还有\`-\`输出"IMPOSSIBLE"
5. 否则输出翻转次数

### 复杂度分析
- 时间复杂度：O(N × K)，最坏情况每个位置都要翻转K个字符
- 空间复杂度：O(N)

## 参考代码

\`\`\`cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    string s;
    cin >> s;

    // Oversized Pancake Flipper：翻转煎饼
    int ans = 0;
    for (int i = 0; i <= n - k; i++) {
        if (s[i] == '-') {
            for (int j = 0; j < k; j++) {
                s[i + j] = (s[i + j] == '+' ? '-' : '+');
            }
            ans++;
        }
    }

    if (s.find('-') != string::npos) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
\`\`\`
