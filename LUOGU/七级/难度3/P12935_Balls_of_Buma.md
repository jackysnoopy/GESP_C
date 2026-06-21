# [NERC 2019] Balls of Buma

## 题目描述

给定一个数组，找出其中最长的连续相同元素序列的长度。

## 输入格式

第一行：n
第二行：n个整数

## 输出格式

输出最长连续相同元素序列的长度

## 提示

数据范围：1 ≤ n ≤ 1000

## 解题思路

### 问题分析
给定一个数组，需要找到最长的连续相同元素的子序列长度。

### 核心思路
1. 遍历数组，维护当前连续长度和最大长度
2. 如果当前元素与前一个相同，当前长度加1
3. 否则，重置当前长度为1
4. 更新最大长度

### 算法流程
1. 读入数组
2. 遍历数组，统计连续相同元素的长度
3. 维护最大值
4. 输出结果

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

\`\`\`cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Balls of Buma：球的最大数量
    // 简化问题：找最大连续相同数
    int maxLen = 1, curLen = 1;
    for (int i = 1; i < n; i++) {
        if (a[i] == a[i - 1]) {
            curLen++;
        } else {
            curLen = 1;
        }
        maxLen = max(maxLen, curLen);
    }

    cout << maxLen << "\n";

    return 0;
}
\`\`\`
