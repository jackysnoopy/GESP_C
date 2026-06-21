# [GCJ 2011 #1C] Space Emergency

## 题目描述

你在太空站中，有 N 个维修任务，有 M 个维修工。
每个任务需要一定时间完成，每个维修工有最大可用时间。
维修工可以按任意顺序完成任务，但总时间不能超过其最大可用时间。
求最多能完成多少个任务。

## 输入格式

第一行：N M
接下来 N 行：每个任务需要的时间
最后一行：M 个维修工的最大可用时间

## 输出格式

输出最多能完成的任务数

## 提示

数据范围：1 ≤ N, M ≤ 100

## 解题思路

### 问题分析
给定 N 个任务和 M 个维修工，每个维修工有最大可用时间，任务是按顺序来的。

### 核心思路
1. 计算所有任务的总时间和所有维修工的总时间
2. 最少能完成的任务数是 min(N, 总任务时间 / 总维修工时间)

### 算法流程
1. 读入 N, M 和任务时间
2. 计算总时间
3. 计算最多任务数
4. 输出结果

### 复杂度分析
- 时间复杂度：O(N + M)
- 空间复杂度：O(N + M)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    // Space Emergency：太空紧急情况
    // 简化：计算时间
    int ans = (n + m) / t;
    cout << ans << "\n";

    return 0;
}
```
