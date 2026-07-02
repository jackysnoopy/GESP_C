# UVA163 - Bridges (桥梁)

## 题目描述

给定一组高度，求最长严格递增子序列的长度。

## 输入格式

每组数据第一行一个整数 n，接着 n 个整数。输入以 `0` 结尾。

## 输出格式

输出最长严格递增子序列的长度。

## 样例

略。

## 提示

本题使用经典的耐心排序（patience sorting）方法求LIS。

## 解题思路

### 问题分析

最长递增子序列（LIS）的经典问题。

### 核心思路

1. 维护一个数组 `result` 存储当前最优序列
2. 对每个新元素，若大于末尾则追加
3. 否则用二分查找替换第一个≥它的元素

### 算法流程

1. 初始化 result 为第一个元素
2. 遍历剩余元素
3. 使用 lower_bound 二分查找
4. 返回 result 的长度

### 复杂度分析

- 时间复杂度：O(N * logN)
- 空间复杂度：O(N)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    bool first = true;
    while (cin >> n && n) {
        if (!first) cout << "\n";
        first = false;
        vector<int> heights(n);
        for (int i = 0; i < n; i++) cin >> heights[i];
        
        vector<int> result;
        result.push_back(heights[0]);
        for (int i = 1; i < n; i++) {
            if (heights[i] > result.back()) {
                result.push_back(heights[i]);
            } else {
                *lower_bound(result.begin(), result.end(), heights[i]) = heights[i];
            }
        }
        cout << result.size() << "\n";
    }
    return 0;
}
```
