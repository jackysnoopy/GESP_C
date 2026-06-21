# [2019 KAIST RUN Fall] Lexicographically Minimum Walk

## 题目描述

There is a directed graph $G$ with $N$ nodes and $M$ edges. Each node is numbered $1$ through $N$, and each edge is numbered $1$ through $M$. For each $i$ ($1 \le i \le M$), edge $i$ goes from vertex $u_i$ to vertex $v_i$ and has a $\textbf{unique}$ color $c_i$.

A $\textit{walk}$ is defined as a sequence of edges $e_1$, $e_2$, $\cdots$, $e_{l}$ where for each $1 \le k < l$, $v_{e_k}$ (the tail of edge $e_k$) is the same as $u_{e_{k+1}}$ (the head of edge $e_{k+1}$). We can say a walk $e_1, e_2, \cdots, e_l$ starts at vertex $u_{e_1}$ and ends at vertex $v_{e_l}$. Note that the same edge can appear multiple times in a walk.

The $\textit{color sequence}$ of a walk $e_1, e_2, \cdots, e_l$ is defined as $c_{e_1}, c_{e_2}, \cdots, c_{e_l}$.

Consider all color sequences of walks of length at most $10^{100}$ from vertex $S$ to vertex $T$ in $G$. Write a program that finds the lexicographically minimum sequence among them.

## 输入格式

The first line of the input contains four space-separated integers $N$, $M$, $S$, and $T$ ($1 \le N \le 100\,000$, $0 \le M \le 300\,000$, $1 \le S \le N$, $1 \le T \le N$, $S \neq T$).

Then $M$ lines follow: the $j$ ($1 \le j \le M$)-th of them contains three space-separated integers $u_i$, $v_i$ and $c_i$ ($1 \le u_i, v_i \le N$, $u_i \neq v_i$, $1 \le c_i \le 10^{9}$); it describes a directional edge from vertex $u_i$ to vertex $v_i$ with color $c_i$.

The graph doesn't have multiple edges and each edge has a unique color. Formally, for any $1 \le i < j \le M$, $c_i \neq c_j$ and $(u_i, v_i) \neq (u_j, v_j)$ holds.

## 输出格式

If there is no walk from vertex $S$ to vertex $T$, print $\texttt{IMPOSSIBLE}$.  (without quotes)

Otherwise, let's say $a_1, a_2, \cdots, a_l$ is the lexicographically minimum sequence among all color sequences of length at most $10^{100}$ from vertex $S$ to vertex $T$.

- If $l \le 10^{6}$, print $a_1, a_2, \cdots, a_l$ in the first line. There should be a space between each printed integer.
- If $l > 10^{6}$, print $\texttt{TOO LONG}$. (without quotes)

## 样例

### 样例输入 1
```
3 3 1 3
1 2 1
2 3 7
1 3 5
```

### 样例输出 1
```
1 7
```

### 样例输入 2
```
3 4 1 3
1 2 1
2 1 2
2 3 7
1 3 5
```

### 样例输出 2
```
TOO LONG
```

### 样例输入 3
```
2 0 2 1
```

### 样例输出 3
```
IMPOSSIBLE
```

## 提示

Sequence $p_1, p_2, \cdots, p_{n}$ is lexicographically smaller than another sequence $q_1, q_2, \cdots, q_{m}$ if and only if one of the following holds:

- There exists a unique $j$ ($0 \le j < \min(n, m)$) where $p_1 = q_1$, $p_2 = q_2$, $\cdots$, $p_{j} = q_{j}$ and $p_{j+1} < q_{j+1}$.
- $n < m$ and $p_1 = q_1$, $p_2 = q_2$, $\cdots$, $p_n = q_n$. In other words, $p$ is a strict prefix of $q$.

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

    int N, M, S, T;
    cin >> N >> M >> S >> T;

    vector<vector<pair<int, int>>> adj(N + 1);
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
    }

    vector<long long> dist(N + 1, 1e18);
    vector<int> parent(N + 1, -1);
    vector<int> edge_color(N + 1, -1);

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    dist[S] = 0;
    pq.push({0, S});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& [v, c] : adj[u]) {
            if (dist[u] + c < dist[v]) {
                dist[v] = dist[u] + c;
                parent[v] = u;
                edge_color[v] = c;
                pq.push({dist[v], v});
            }
        }
    }

    if (dist[T] == 1e18) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    vector<int> path;
    int cur = T;
    while (cur != S) {
        path.push_back(edge_color[cur]);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());

    if (path.size() > 1000000) {
        cout << "TOO LONG\n";
    } else {
        for (int i = 0; i < (int)path.size(); i++) {
            if (i) cout << " ";
            cout << path[i];
        }
        cout << "\n";
    }

    return 0;
}
```
