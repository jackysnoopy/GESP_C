# P2255 - [USACO14JAN] Recording the Moolympics S

## 题目描述

参见洛谷原题。

## 解题思路

### 问题分析

N 个节目，每个有开始和结束时间。有 2 个调谐器，可以同时录制 2 个节目。求最多能录制多少个节目。

### 核心思路

**贪心算法**：按开始时间排序，对每个节目尝试分配到两个调谐器中空闲的那个。

### 算法流程

1. 按开始时间排序所有节目
2. 维护两个调谐器的结束时间 end1, end2
3. 对每个节目 (s, e)：
   - 如果 s ≥ end1，分配到调谐器 1
   - 否则如果 s ≥ end2，分配到调谐器 2
   - 否则跳过

### 复杂度分析

- 时间复杂度：O(N log N)
- 空间复杂度：O(N)

### 关键技巧

- 经典区间调度问题的扩展（2 机器版本）
- 贪心策略：总是分配到最早空闲的调谐器

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
    vector<pair<int, int>> seg(n);
    for (int i = 0; i < n; i++) cin >> seg[i].first >> seg[i].second;
    sort(seg.begin(), seg.end());
    int end1 = -1, end2 = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int s = seg[i].first, e = seg[i].second;
        if (s >= end1) { end1 = e; ans++; }
        else if (s >= end2) { end2 = e; ans++; }
    }
    cout << ans << "\n";
    return 0;
}
```
