# P12135 检测器连通

## 题目描述

给定一个 2×n 的网格，其中某些位置放置了检测器（用 `#` 表示），其余位置为空（用 `.` 表示）。检测器之间如果在上下左右四个方向相邻，则它们是连通的。

要求计算：最少还需要在空位置放置多少个检测器，才能使所有检测器连通成一个连通分量。

## 输入格式

两行字符串，每行长度为 n，包含字符 `#` 和 `.`：
- 第一行：网格第一行
- 第二行：网格第二行

## 输出格式

一个整数：最少需要额外放置的检测器数量。

## 样例

**样例输入：**
```
#..#
.#.#
```

**样例输出：**
```
1
```

## 提示

- 保证网格中至少有一个检测器
- 1 ≤ n ≤ 1000

## 解题思路

### 问题分析

本题的核心是：给定一个 2×n 的网格中的检测器集合，求最少添加多少个检测器使得所有检测器连通。

### 核心思路

使用**并查集（Union-Find）**来处理连通性问题：

1. 将网格中的每个位置映射为节点：第一行的第 i 列对应节点 i，第二行的第 i 列对应节点 n+i
2. 对于所有检测器位置，建立并查集
3. 合并相邻的检测器（上下相邻、左右相邻）
4. 统计连通分量数量 components
5. 最少需要添加的检测器数量 = components - 1（用一条边连接两个连通分量，需要一个新节点）

### 算法流程

1. 读入两行字符串
2. 遍历网格，标记所有检测器位置，统计检测器总数
3. 合并上下相邻的检测器
4. 合并同行左右相邻的检测器
5. 统计不同根节点的数量，得到连通分量数
6. 答案 = 连通分量数 - 1

### 复杂度分析

- 时间复杂度：O(n × α(n))，其中 α 是反阿克曼函数，近似 O(1)
- 空间复杂度：O(n)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct UnionFind {
    vector<int> parent, rank;
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) parent[px] = py;
        else if (rank[px] > rank[py]) parent[py] = px;
        else { parent[py] = px; rank[px]++; }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string row1, row2;
    cin >> row1 >> row2;
    int n = row1.length();
    UnionFind uf(2 * n);
    vector<bool> is_detector(2 * n, false);
    for (int i = 0; i < n; i++) {
        if (row1[i] == '#') is_detector[i] = true;
        if (row2[i] == '#') is_detector[n + i] = true;
    }
    for (int i = 0; i < n; i++) {
        if (is_detector[i] && is_detector[n + i]) uf.unite(i, n + i);
        if (i < n - 1) {
            if (is_detector[i] && is_detector[i + 1]) uf.unite(i, i + 1);
            if (is_detector[n + i] && is_detector[n + i + 1]) uf.unite(n + i, n + i + 1);
        }
    }
    int components = 0;
    vector<bool> seen(2 * n, false);
    for (int i = 0; i < 2 * n; i++) {
        if (is_detector[i]) {
            int root = uf.find(i);
            if (!seen[root]) { seen[root] = true; components++; }
        }
    }
    cout << max(0, components - 1) << endl;
    return 0;
}
```
