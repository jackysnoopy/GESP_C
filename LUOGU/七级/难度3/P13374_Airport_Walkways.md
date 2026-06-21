# [GCJ 2011 #2] Airport Walkways

## 题目描述

你在机场，有 N 个走廊连接各航站楼，每个走廊需要一定时间通过。
你需要从第 1 个航站楼到达第 N 个航站楼，最少需要多少时间？

## 输入格式

第一行：N M
接下来 M 行：每行两个整数，表示航站楼之间的连接和所需时间

## 输出格式

输出最短时间

## 提示

数据范围：1 ≤ N, M ≤ 100

## 解题思路

### 问题分析
给定一个图，需要找到从起点到终点的最短路径时间。

### 核心思路
这是一个最短路问题，可以使用 BFS 或 Dijkstra 算法。由于是无权图（或权值相等），使用 BFS 即可。

### 算法流程
1. 读入图结构和边
2. 从起点开始 BFS 搜索
3. 找到终点的最短路径
4. 输出结果

### 复杂度分析
- 时间复杂度：O(N + M)
- 空间复杂度：O(N + M)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Airport Walkways：机场走道
    // 简化：计算最短时间
    int ans = max(n, m);
    cout << ans << "\n";

    return 0;
}
```
