# [SCCPC 2021] Don't Really Like How The Story Ends

## 题目描述

There are $n$ planets in the galaxy, and many undirected warp tunnels connecting them. $6000$ years ago, Spinel performed a depth-first search on the planets, visited all of them, and labeled them from $1$ to $n$ in the order of discovery. 

Many warp tunnels have broken down since, and only $m$ of them are still working. Spinel wants to know how many new warp tunnels have to be built so that it is possible to perform a depth-first search, where the order of discovery is exactly as labeled $6000$ years ago.

Recall that the depth-first search (DFS) algorithm inputs a graph $\textit{G}$ and a vertex $\textit{v}$ of $\textit{G}$, and labels all vertices reachable from $\textit{v}$ as discovered.

Here is the pseudocode of a recursive implementation of DFS:

```
procedure DFS(G, v) is
    label v as discovered
    for all vertices w that there exists an edge between v and w do
        if vertex w is not labeled as discovered then
            recursively call DFS(G, w)
```

## 输入格式

There are multiple test cases. The first line of the input contains an integer $T$ indicating the number of test cases. For each test case:

The first line contains two integers $n$ and $m$ ($1 \le n,m \le 10^5$) indicating the number of planets and the number of remaining warp tunnels.

For the following $m$ lines, the $i$-th line contains two integers $u_i$ and $v_i$ ($1 \le u_i,v_i \le n$) indicating a warp tunnel between $u_i$ and $v_i$.

It's guaranteed that the sum of $(n + m)$ of all test cases will not exceed $10^6$.

## 输出格式

For each test case output one line containing one integer, indicating the minimum number of new warp tunnels that have to be built.

## 样例

### 样例输入 1
```
3
2 3
1 1
1 2
2 1
4 1
1 4
4 2
1 2
3 4
```

### 样例输出 1
```
0
2
1
```

## 提示

For the second sample test case we can add a tunnel between planet $1$ and $2$, and add another tunnel between planet $2$ and $3$.

For the third sample test case we can add a tunnel between planet $2$ and $3$.

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
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n + 1, false);
        int components = 0;

        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                components++;
                vector<int> stack;
                stack.push_back(i);
                visited[i] = true;

                while (!stack.empty()) {
                    int u = stack.back();
                    stack.pop_back();
                    for (int v : adj[u]) {
                        if (!visited[v]) {
                            visited[v] = true;
                            stack.push_back(v);
                        }
                    }
                }
            }
        }

        cout << components - 1 << "\n";
    }

    return 0;
}
```

## 解题思路

### 问题分析

给定 $n$ 个星球和 $m$ 条无向隧道，要求添加最少的隧道，使得存在一种 DFS 遍历顺序恰好为 $1, 2, \ldots, n$。

### 核心思路

关键观察：由于 DFS 的邻接表遍历顺序可以任意排列，只要所有星球连通，就可以通过合理排列邻接表顺序来实现 $1, 2, \ldots, n$ 的发现顺序。因此问题等价于计算当前图的连通分量数，答案为连通分量数减一。

### 算法流程

1. 读入 $n$ 个星球和 $m$ 条边，建立邻接表。
2. 使用 DFS/BFS（非递归栈实现）遍历图，统计连通分量个数 `components`。
3. 输出 `components - 1`，即需要添加的最少边数。

### 复杂度分析

- **时间复杂度**：$O(n + m)$，每个顶点和每条边各被访问一次。
- **空间复杂度**：$O(n + m)$，邻接表和访问数组各占线性空间。
