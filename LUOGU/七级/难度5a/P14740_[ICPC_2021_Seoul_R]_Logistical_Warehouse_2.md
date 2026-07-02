# [ICPC 2021 Seoul R] Logistical Warehouse 2

## 题目描述

KOPANG is one of largest online vendors in Korea and introduced so called "early-morning delivery" for the first time. To cope with the growing demand, KOPANG plans to build new logistical warehouses. The locations of logistical warehouses must be within a certain distance from customers to keep the delivery time guaranteed by KOPANG to the customers.

The logistics network is modelled as a connected tree $T$. Each node of $T$ represents a region such as a city or a province in Korea, and each edge of $T$ represents a transportation road connecting two regions. KOPANG wants to select one or more nodes of $T$ satisfying the **distance restriction** for the logistical warehouses. Before the selection, KOPANG first fixed a distance parameter $K$ through sufficient research. KOPANG now wants to select the minimum number of nodes satisfying the distance restriction that the distance from every node of $T$ to its closest selected node (warehouse) is at most $K$. The distance of two nodes $u$ and $v$ is the number of edges of the (unique) path in $T$ that connects $u$ and $v$. Note that the distance is defined as zero if $u = v$.

For example, Figure G.1 below shows a tree $T$ with nine nodes and eight edges. For $K = 1$, if three warehouses are located at nodes 2, 5, and 8, marked with red circles as in Figure G.1 (a), then the distance of every node of $T$ to the closest warehouse is at most one. Two warehouses are not enough to satisfy the distance restriction, so three warehouses are the minimum. For $K = 2$, three warehouses are still required; warehouses at nodes 2, 5, and 8 for $K = 1$ are the ones for $K = 2$. Of course, the locations of the minimum number of warehouses are not unique; three warehouses at nodes 4, 7, and 1 as in Figure G.1 (b) also satisfy the distance restriction for $K = 2$.

Given a connected tree $T$ and a positive integer $K$, write a program to select the minimum number of nodes (warehouses) of $T$ satisfying the distance restriction, that is, the distance of every node of $T$ to its closest warehouse is at most $K$.

![Figure G.1 The nodes marked with red circles are the ones selected for warehouses.](https://cdn.luogu.com.cn/upload/image_hosting/j51fgnld.png)

## 输入格式

Your program is to read from standard input. The input starts with a line containing two integers $n$ and $K$ ($1 \le K \le n \le 10^5$), where $n$ is the number of nodes in a connected tree and the maximum distance from each node in the tree to its closest selected node is at most $K$. In the following $n-1$ lines, the edge information is given; the $i$-th line contains two positive integers representing two indices of the end nodes of the $i$-th edge. The nodes are indexed from 1 to $n$.

## 输出格式

Your program is to write to standard output. Print exactly one line that contains the minimum number of the selected nodes for logistical warehouses satisfying the distance restriction for the given tree and the distance parameter $K$.

## 样例

### 样例 1
**输入：**
```
9 1
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
```
**输出：**
```
3
```

### 样例 2
**输入：**
```
9 2
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
```
**输出：**
```
3
```

### 样例 3
**输入：**
```
9 8
2 1
7 3
3 4
4 5
6 5
7 8
3 2
8 9
```
**输出：**
```
1
```

## 提示

（无）

## 解题思路

### 问题分析

本题要求在树上选择最少的节点作为仓库，使得每个节点到最近仓库的距离不超过K。

### 核心思路

使用贪心算法：
1. 对树进行DFS，计算每个节点的深度
2. 使用动态规划计算每个节点需要的仓库数量
3. 当某个节点的dp值等于K时，需要在此处放置仓库

### 算法流程

1. 构建树的邻接表
2. 进行DFS计算深度和父节点
3. 使用DP计算每个节点需要的仓库数量
4. 统计满足条件的仓库数量

### 复杂度分析

- 时间复杂度：$O(n)$，其中n是节点数量
- 空间复杂度：$O(n)$，用于存储树结构和DP数组

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXN];
int dp[MAXN];

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u);
        }
    }
}

void dfs2(int u, int p, int k) {
    dp[u] = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u, k);
            dp[u] = max(dp[u], dp[v] + 1);
        }
    }
    if (dp[u] == k) {
        dp[u] = -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    depth[0] = -1;
    dfs1(1, 0);
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] == k) {
            ans++;
        }
    }
    
    cout << max(1, ans) << "\n";
    
    return 0;
}
```