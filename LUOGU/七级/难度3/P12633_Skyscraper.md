# [UOI 2020] Skyscraper

## 题目描述

给定n栋摩天大楼的高度，求任意两栋大楼的最大高度差。

## 输入格式

第一行n
第二行n个整数表示高度

## 输出格式

输出最大高度差

## 提示

数据范围：1 ≤ n ≤ 1000

## 解题思路

### 问题分析
找数组中的最大值和最小值，它们的差即为最大高度差。

### 核心思路
遍历一遍数组找最大最小值。

### 算法流程
1. 初始化最大值 maxVal 和最小值 minVal
2. 遍历数组，更新 maxVal = max(maxVal, a[i])，minVal = min(minVal, a[i])
3. 返回 maxVal - minVal

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码

```cpp
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

    // Skyscraper：摩天大楼
    // 计算最大高度差
    int maxDiff = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            maxDiff = max(maxDiff, abs(a[i] - a[j]));
        }
    }

    cout << maxDiff << "\n";

    return 0;
}
```
