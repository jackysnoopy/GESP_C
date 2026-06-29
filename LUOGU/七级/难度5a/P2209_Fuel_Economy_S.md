# [USACO13OPEN] Fuel Economy S

## 题目描述

Farmer John 决定去一次跨国旅游度假。为了不让他的奶牛们感到被抛弃，他决定租一辆大卡车来带他的奶牛们一起旅行。

这辆卡车有一个很大的油箱，可以装下 G 个单位的油，不幸的是，卡车的耗油量也很大，卡车每运动一个单位的距离，就要消耗一个单位的油。Farmer John 要在他的旅程中走 D 个单位的距离。

因为 FJ 知道他可能要几次在旅途中停下，给油箱加油，所以他把在旅途沿路上的 N 个加油站的记录做成了表格。对于第 i 个加油站，他记录了加油站与起点的距离 X_i，以及加油站中每单位油的价格 Y_i。

已知以上所给的信息，以及 FJ 在路途开始时拥有的燃油的数量 B，请计算出 FJ 到达目的地时花费的油费用的最小值。如果 FJ 无法到达旅途的终点，那么请输出 -1。

## 输入格式

第一行： 四个整数：N, G, B, D。

接下来 N 行：每一行都有两个整数 X_i 与 Y_i，意义如上所述。

## 输出格式

一个整数，如果 FJ 无法到达旅途的终点，那么输出 -1，否则输出 FJ 到达目的地时花费的油费用的最小值。

## 样例

Sample 1:
Input:
4 10 3 17
2 40
9 15
5 7
10 12
Output:
174

## 提示

(无)

## 解题思路

### 问题分析
- 卡车油箱容量 G，初始油量 B，总距离 D。
- 沿途有 N 个加油站，每个加油站有距离和油价。
- 求最小加油费用。

### 核心思路
- 贪心策略：在当前加油站加油，只加到能到达下一个更便宜加油站的量。
- 如果没有更便宜的加油站，加满油箱。

### 算法流程
1. 按距离排序所有加油站，添加终点。
2. 对每个加油站，找到下一个更便宜的加油站。
3. 如果没有更便宜的，加满；否则加到刚好能到达下一个更便宜的量。
4. 检查能否到达下一个加油站。

### 复杂度分析
- 时间复杂度：O(N^2)
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
    
    int n, g, b, d;
    cin >> n >> g >> b >> d;
    
    vector<pair<int, int>> stations(n);
    for (int i = 0; i < n; i++) {
        cin >> stations[i].first >> stations[i].second;
    }
    
    sort(stations.begin(), stations.end());
    stations.push_back({d, 0});
    
    long long ans = 0;
    int cur_fuel = b;
    int last_pos = 0;
    
    for (int i = 0; i < n; i++) {
        int dist = stations[i].first - last_pos;
        if (cur_fuel < dist) {
            cout << -1 << "\n";
            return 0;
        }
        cur_fuel -= dist;
        
        int next_cheaper = -1;
        for (int j = i + 1; j <= n; j++) {
            if (stations[j].second < stations[i].second) {
                next_cheaper = j;
                break;
            }
        }
        
        if (next_cheaper == -1) {
            int need = g - cur_fuel;
            ans += (long long)need * stations[i].second;
            cur_fuel = g;
        } else {
            int need_to_reach = stations[next_cheaper].first - stations[i].first;
            int need = max(0, need_to_reach - cur_fuel);
            need = min(need, g - cur_fuel);
            if (need > 0) {
                ans += (long long)need * stations[i].second;
                cur_fuel += need;
            }
        }
        
        last_pos = stations[i].first;
    }
    
    cout << ans << "\n";
    return 0;
}

```
