# [USACO1.2] 挤牛奶 Milking Cows

## 题目描述

三个农民每天清晨 $5$ 点起床，然后去牛棚给三头牛挤奶。

第一个农民在 $300$ 秒（从 $5$ 点开始计时）给他的牛挤奶，一直到 $1000$ 秒。第二个农民在 $700$ 秒开始，在 $1200$ 秒结束。第三个农民在 $1500$ 秒开始，$2100$ 秒结束。  

期间最长的至少有一个农民在挤奶的连续时间为 $900$ 秒（从 $300$ 秒到 $1200$ 秒），而最长的无人挤奶的连续时间（从挤奶开始一直到挤奶结束）为 $300$ 秒（从 $1200$ 秒到 $1500$ 秒）。

---
你的任务是编一个程序，读入一个有 $n$ 个农民挤 $n$ 头牛的工作时间列表，计算以下两点（均以秒为单位）：

1. 最长至少有一人在挤奶的时间段。
2. 最长的无人挤奶的时间段。（从有人挤奶开始算起）

## 输入格式

第一行一个正整数 $n$。

接下来 $n$ 行，每行两个非负整数 $l,r$，表示一个农民的开始时刻与结束时刻。

## 输出格式

仅一行两个整数，以一个空格分隔，即题目所要求的两个答案。

## 样例 #1

**输入**
```
3
300 1000
700 1200
1500 2100
```

**输出**
```
900 300
```

## 提示

【数据范围】  
对于 $100\%$ 的数据，$1\le n \le 5000$，$0 \le l \le r \le 10^6$。

题目翻译来自 NOCOW。

USACO Training Section 1.2

## 解题思路

### 问题分析

$N$ 个农民，每人有挤奶的起止时间 $[l_i, r_i)$。求至少有一头牛在挤奶的最长连续时间和没有牛挤奶的最长连续时间。

### 核心思路

**差分统计 + 扫描。** 使用差分数组统计每个时间点的奶牛数，然后扫描数组找出连续有牛和无牛的区间长度。

### 算法流程

1. 找出最晚的结束时间 $max\_t$。
2. 差分标记每个区间：$diff[l] += 1$，$diff[r] -= 1$。
3. 从 $0$ 到 $max\_t$ 扫描：
   - $cur += diff[i]$。
   - 如果 $cur > 0$：有牛状态，更新有牛最长区间。
   - 如果 $cur == 0$：无牛状态，更新无牛最长区间。
4. 输出两个最长长度。

### 复杂度分析

- **时间复杂度：** $O(max\_t + N)$。
- **空间复杂度：** $O(max\_t)$。

### 要点

- 时间点从 $0$ 开始，区间是左闭右开 $[l, r)$。
- $max\_t$ 是最大结束时间，如果坐标范围太大，需要离散化。
- 注意最后一头奶牛挤完奶后可能仍有时间点，但扫描到 $max\_t$ 即可。

## 参考代码
## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    int max_t = 0;
    vector<pair<int,int>> seg(N);
    for (int i = 0; i < N; i++) {
        cin >> seg[i].first >> seg[i].second;
        max_t = max(max_t, seg[i].second);
    }
    vector<int> d(max_t + 2, 0);
    for (auto &s : seg) { d[s.first]++; d[s.second]--; }
    int cur = 0, milk_max = 0, idle_max = 0, milk_s = -1, idle_s = -1;
    for (int i = 0; i <= max_t; i++) {
        cur += d[i];
        if (cur > 0) {
            if (milk_s == -1) milk_s = i;
            if (idle_s != -1) { idle_max = max(idle_max, i - idle_s); idle_s = -1; }
        } else {
            if (idle_s == -1) idle_s = i;
            if (milk_s != -1) { milk_max = max(milk_max, i - milk_s); milk_s = -1; }
        }
    }
    if (milk_s != -1) milk_max = max(milk_max, max_t - milk_s);
    cout << milk_max << " " << idle_max << "\n";
    return 0;
}
```
