# P2207 - [USACO13OPEN] Photo B

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

有 n 头奶牛排成一排，k 对关系不好的奶牛不能在同一张照片中。每张照片拍摄一个连续区间。求最少需要多少张照片使得每头奶牛至少出现在一张照片中。

### 核心思路

**贪心算法**：从位置 1 开始，每次取最长的有效区间。

对于起始位置 pos，有效区间 [pos, r] 要求：对所有坏对 (a,b)，不能同时有 a ≥ pos 且 b ≤ r。因此 r ≤ min{b : 坏对 (a,b) 且 a ≥ pos} - 1。

### 算法流程

1. 将坏对按左端点排序
2. 从 pos=1 开始，找到所有 a ≥ pos 的坏对中最小的 b
3. 区间为 [pos, minB-1]，拍照数 +1
4. pos 移到 minB，重复直到覆盖所有奶牛

### 复杂度分析

- 时间复杂度：O(k log k)
- 空间复杂度：O(k)

### 关键技巧

- n 可达 10^9，不能直接枚举位置
- 利用坏对数量少（k ≤ 1000）的特点，只在坏对的端点处进行决策
- 每步至少跳过一个坏对，保证算法效率

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int k;
    cin >> n >> k;
    vector<pair<long long, long long>> bad(k);
    for (int i = 0; i < k; i++) {
        cin >> bad[i].first >> bad[i].second;
        if (bad[i].first > bad[i].second) swap(bad[i].first, bad[i].second);
    }
    sort(bad.begin(), bad.end());
    long long ans = 0;
    long long pos = 1;
    int idx = 0;
    while (pos <= n) {
        long long minB = n + 1;
        while (idx < k && bad[idx].first < pos) idx++;
        for (int j = idx; j < k; j++) {
            minB = min(minB, bad[j].second);
        }
        long long r = minB - 1;
        if (r < pos) r = pos;
        ans++;
        pos = r + 1;
    }
    cout << ans << "\n";
    return 0;
}
```
