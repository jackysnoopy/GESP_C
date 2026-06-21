# [AMPPZ 2019] Assimilation

## 题目描述

给定一个数组，计算其中位数。

## 输入格式

第一行：n
第二行：n个整数

## 输出格式

输出中位数

## 提示

数据范围：1 ≤ n ≤ 1000

## 解题思路

### 问题分析
给定一个数组，需要找到其中位数。

### 核心思路
1. 对数组进行排序
2. 如果数组长度为奇数，中位数是中间元素
3. 如果数组长度为偶数，中位数是中间两个元素的平均值

### 算法流程
1. 读入数组
2. 排序数组
3. 根据奇偶性计算中位数
4. 输出结果

### 复杂度分析
- 时间复杂度：O(n log n) 用于排序
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

    // Assimilation：排序后找中位数
    sort(a.begin(), a.end());

    if (n % 2 == 1) {
        cout << a[n / 2] << "\n";
    } else {
        cout << (a[n / 2 - 1] + a[n / 2]) / 2 << "\n";
    }

    return 0;
}
```
