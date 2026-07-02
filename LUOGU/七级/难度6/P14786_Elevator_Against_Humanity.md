# P14786 [NERC 2025] Elevator Against Humanity

## 题目描述

n人在不同楼层等电梯，每人有起点s_i和终点f_i。电梯从1楼出发，目标是最大化总时间。

## 输入格式

多组数据。每组：n，n行s_i f_i。

## 输出格式

每组一行：最大时间。

## 解题思路

### 核心思路
- 贪心：交替访问最远的起点和最近的终点
- 最大化每次移动的距离

### 复杂度
- 时间: O(n log n)
- 空间: O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> people(n);
        for (int i = 0; i < n; i++) cin >> people[i].first >> people[i].second;
        vector<long long> starts, dests;
        for (auto& p : people) { starts.push_back(p.first); dests.push_back(p.second); }
        sort(starts.begin(), starts.end());
        sort(dests.begin(), dests.end(), greater<long long>());
        long long total = 0;
        long long current = 1;
        vector<long long> visits;
        int si = 0, di = 0;
        while (si < (int)starts.size() || di < (int)dests.size()) {
            long long ns = (si < (int)starts.size()) ? starts[si] : -1;
            long long nd = (di < (int)dests.size()) ? dests[di] : -1;
            if (ns == -1) { visits.push_back(nd); di++; }
            else if (nd == -1) { visits.push_back(ns); si++; }
            else if (abs(ns - current) >= abs(nd - current)) { visits.push_back(ns); si++; }
            else { visits.push_back(nd); di++; }
        }
        for (long long v : visits) { total += abs(v - current); current = v; }
        cout << total << "\n";
    }
    return 0;
}
```
