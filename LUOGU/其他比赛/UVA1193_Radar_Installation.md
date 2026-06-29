# Radar Installation

## 题目描述

在海岸线上有一排岛屿，每个岛屿有一个坐标 (x, y)。需要在海岸线（x 轴）上放置雷达，雷达的覆盖半径为 d。求覆盖所有岛屿所需的最少雷达数量。若无法覆盖所有岛屿则输出 -1。

## 输入格式

- 多组测试数据，每组第一行两个整数 n 和 d
- 接下来 n 行，每行两个整数 x 和 y，表示岛屿坐标
- 输入以 "0 0" 结束

## 输出格式

每组数据输出 "Case i: k"，其中 k 为最少雷达数量或 -1

## 样例

```
输入：
3 2
1 2
-3 1
2 1
0 0

输出：
Case 1: 2
```

## 提示

- 将每个岛屿转换为海岸线上的覆盖区间
- 使用贪心算法，按区间右端点排序后依次放置雷达

## 解题思路

### 问题分析

每个岛屿 (x, y) 需要雷达覆盖，雷达在 x 轴上，覆盖半径为 d。当 y > d 时，该岛屿无法被覆盖。

### 核心思路

将每个岛屿转换为海岸线上的覆盖区间 [x - dx, x + dx]，其中 dx = √(d² - y²)。然后使用贪心区间覆盖算法：按右端点排序，依次放置雷达。

### 算法流程

1. 对于每个岛屿 (x, y)：
   - 若 y > d，无法覆盖，输出 -1
   - 否则计算覆盖区间 [x - √(d² - y²), x + √(d² - y²)]
2. 将所有区间按右端点排序
3. 贪心放置雷达：
   - 维护当前雷达位置 pos
   - 遍历每个区间，若区间左端点 > pos，则需要新雷达，放置在区间右端点
4. 输出雷达数量

### 复杂度分析

- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Interval {
    double l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, d, cas = 0;
    while (cin >> n >> d) {
        if (n == 0 && d == 0) break;
        
        vector<Interval> intervals;
        bool possible = true;
        
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            if (y > d) {
                possible = false;
            } else {
                double dx = sqrt((double)d * d - (double)y * y);
                intervals.push_back({x - dx, x + dx});
            }
        }
        
        if (!possible) {
            cout << "Case " << ++cas << ": -1\n";
            continue;
        }
        
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });
        
        int ans = 0;
        double pos = -1e9;
        for (const auto& inv : intervals) {
            if (pos + 1e-9 < inv.l) {
                ans++;
                pos = inv.r;
            }
        }
        
        cout << "Case " << ++cas << ": " << ans << "\n";
    }
    
    return 0;
}
```
