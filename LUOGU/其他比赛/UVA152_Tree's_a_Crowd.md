# UVA152 - Tree's a Crowd (树群)

## 题目描述

给定 n 个三维空间中的点 (x,y,z)，对每个点计算它到其他所有点的距离，找到最小距离。统计有多少点的最小距离在 [0,1), [1,2), ..., [24,25) 范围内。输出直方图（跳过末尾的 0 计数）。

## 解题思路

### 问题分析

这是一个三维空间中的距离计算问题。对于每个点，需要计算它到所有其他点的距离，并找到最小值。

### 核心思路

使用暴力枚举法，对每个点计算到所有其他点的距离，记录最小值，然后统计直方图。

### 算法流程

1. 读取所有点
2. 对每个点 i：
   - 计算到所有其他点 j 的距离
   - 找到最小距离
   - 将最小距离放入对应的桶中
3. 输出直方图

### 复杂度分析

- 时间复杂度：O(n^2)
- 空间复杂度：O(n)

## 代码实现

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Point> points;
    int x, y, z;
    while (cin >> x >> y >> z && (x != 0 || y != 0 || z != 0)) {
        points.push_back({x, y, z});
    }

    vector<int> histogram(25, 0);

    for (size_t i = 0; i < points.size(); ++i) {
        double minDist = 1e9;
        for (size_t j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            double dist = sqrt(pow(points[i].x - points[j].x, 2) +
                               pow(points[i].y - points[j].y, 2) +
                               pow(points[i].z - points[j].z, 2));
            minDist = min(minDist, dist);
        }
        int bucket = min((int)minDist, 24);
        histogram[bucket]++;
    }

    for (int i = 0; i < 25; ++i) {
        cout << histogram[i] << "\n";
    }

    return 0;
}
```
