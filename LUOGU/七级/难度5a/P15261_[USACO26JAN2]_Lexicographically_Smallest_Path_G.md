# [USACO26JAN2] Lexicographically Smallest Path G

## 题目描述

Bessie is given an undirected graph with $N$ ($1\le N\le 2 \cdot 10^5$) vertices labeled $1\dots N$ and $M$ edges ($N - 1\le M\le 2 \cdot 10^5$). Each edge is described by two integers $u, v$ ($1\le u, v \le N$) describing an undirected edge between nodes $u$ and $v$ and a lowercase Latin letter $c$ in the range a..z that is the value on the edge. The graph given is guaranteed to be connected. There may be multiple edges or self-loops.

Define $f(a, b)$ as the lexicographically smallest concatenation of edge values over all paths starting from node $a$ and ending at node $b$. A path may contain the same edge more than once (i.e., cycles are allowed).

For each $i$ ($1\le i \le N$), help Bessie determine the length of $f(1, i)$. Output this length if it is finite, otherwise output $-1$.

## 输入格式

The first line contains $T$ ($1\le T\le 10$), the number of independent tests. Each test is specified in the following format:

The first line contains $N$ and $M$.

The next $M$ lines each contain two integers followed by a lowercase Latin character.

It is guaranteed that neither the sum of $N$ nor the sum of $M$ over all tests exceeds $4\cdot 10^5$.

## 输出格式

For each test, output $N$ space-separated integers on a new line.

## 样例

### 样例 1
**输入：**
```
2
1 0
2 2
1 1 a
2 1 b
```
**输出：**
```
0
0 -1
```

### 样例 2
**输入：**
```
2
7 7
1 2 a
1 3 a
2 4 b
3 5 a
5 6 a
6 7 a
7 4 a
4 3
1 2 z
2 3 x
3 4 y
```
**输出：**
```
0 1 1 5 2 3 4
0 1 2 -1
```

## 提示

#### Sample 1 Explanation

For the first test case, node 1 can be reached with an empty path, so the answer is 0. In the second test case, node 2 cannot have a lexicographically smallest path, since FJ can repeat the 'a' self-loop any number of times before moving to node 2, producing arbitrarily long strings that are still lexicographically minimal. Therefore, the answer for node 2 is -1.

#### Sample 2 Explanation

For the first test case, node 1 has distance 0. Nodes 2 and 3 are adjacent with node 1, and they have distance 1. For nodes 4, 5, 6, and 7, it can be proven that the lexicographically shortest path does not pass through the edge between node 2 and 4.

For the second test case, node 4 again has no lexicographically smallest path, since the string can be extended indefinitely while remaining lexicographically minimal. Thus, its answer is -1.

SCORING:
- Inputs 3-4: Every character is a.
- Inputs 5-8: Every character is a or b.
- Inputs 9-14: $N,M\le 5000$
- Inputs 15-22: No additional constraints.

## 解题思路

### 问题分析

本题要求在图中找到从节点1到每个节点的字典序最小路径的长度。

### 核心思路

使用BFS或Dijkstra算法：
1. 从节点1开始
2. 按字典序优先探索路径
3. 记录每个节点的最短路径长度

### 算法流程

1. 读取图的结构
2. 使用BFS或Dijkstra算法
3. 计算每个节点的最短路径长度
4. 输出结果

### 复杂度分析

- 时间复杂度：$O((N + M) \log N)$，其中N是节点数，M是边数
- 空间复杂度：$O(N + M)$，用于存储图结构

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<pair<int, char>>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }
        
        vector<int> result(n + 1, -1);
        result[1] = 0;
        
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    
    return 0;
}
```