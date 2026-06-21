# Radar Installation

## 题目描述
[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=246&page=show_problem&problem=3634

[PDF](https://uva.onlinejudge.org/external/11/p1193.pdf)

## 输入格式
（无输入格式）

## 输出格式
（无输出格式）

## 样例
### 样例 1
```
3 2
1 2
-3 1
2 1

1 2
0 2

0 0
```
```
Case 1: 2
Case 2: 1
```

## 解题思路

### 问题分析
x 轴上方有 n 个岛屿，x 轴上安装雷达，每个雷达覆盖半径为 d。求覆盖所有岛屿的最少雷达数。

### 核心思路
每个岛屿对应 x 轴上一个区间 [x-√(d²-y²), x+√(d²-y²)]。问题转化为最少点覆盖所有区间。

### 算法流程
1. 读入 n, d 及岛屿坐标
2. 对每个岛屿计算雷达覆盖区间（若 y>d 则不可能）
3. 按区间右端点排序
4. 贪心选点：每次选右端点，跳过被覆盖的区间
5. 输出最少雷达数

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
