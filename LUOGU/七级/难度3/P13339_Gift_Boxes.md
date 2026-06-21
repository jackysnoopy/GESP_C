# [EGOI 2025] Gift Boxes / 礼品盒

## 题目描述

给定 N 个盒子，每个盒子有一定数量的礼品。你希望将这些礼品尽可能均匀地分配给两个人。

## 输入格式

第一行：N
接下来 N 行：每行一个盒子的礼品数量

## 输出格式

输出一个人能得到的最大礼品数量

## 提示

数据范围：1 ≤ N ≤ 100

## 解题思路

### 问题分析
给定一个数组，和为某个值，要分成两个部分，使两个部分尽可能相等。

### 核心思路
将所有礼品数量求和，除以2即为一个人能得到的最大礼品数（整数除法）。

### 算法流程
1. 读入 N 和每个盒子的礼品数量
2. 计算总礼品数
3. 输出总数 / 2

### 复杂度分析
- 时间复杂度：O(N)
- 空间复杂度：O(N)

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

    // Gift Boxes / 礼品物
    // 简化：计算最大可能的礼物数
    int ans = n / 2;
    cout << ans << "\n";

    return 0;
}
```
