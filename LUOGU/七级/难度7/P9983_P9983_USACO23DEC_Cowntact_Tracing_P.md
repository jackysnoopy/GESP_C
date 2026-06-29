# P9983 [USACO23DEC] Cowntact Tracing P

## 题目描述

Farmer John 有依次编号为 $1\dots N$ 的 $N$ 头奶牛，奶牛间的关系可以用树结构描述。不幸的是，有一种疾病正在传播。

最初，有一些奶牛被感染。每到夜晚，被感染的奶牛会将疾病传播给它的邻居。一旦奶牛被感染，她就会持续处于感染状态。

你将得到 $Q$ 个不同的夜晚数，对于每个夜晚数，请找出最少有多少头奶牛最初可能感染了这种疾病。

## 输入格式

第一行为一个整数 $N$。
接下来一行，包含长度为 $N$ 的由 $1$ 和 $0$ 组成的位串。
接下来 $N-1$ 行描述了树的边。
接着输入 $Q$ 和 $Q$ 个夜晚数。

## 输出格式

输出 $Q$ 行，表示每个夜晚数的答案。若无解，输出 $-1$。

## 样例

### 样例1
输入：
```
5
01001
1 2
2 3
3 4
4 5
6
0 1 2 3 4 5
```
输出：
```
2
1
1
1
1
-1
```

## 提示

$2\le N \le 10^5$，$1\le Q \le 20$。

## 解题思路

### 问题分析

这是一个图论问题。需要计算最少初始感染奶牛数。

### 核心思路

**BFS+贪心**：使用BFS计算感染范围。

### 复杂度分析

- **时间复杂度**：$O(Q \cdot N)$
- **空间复杂度**：$O(N)$

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int infected[MAXN];
int n;

void dfs(int u, int p, int dist, vector<int>& candidates, int max_dist) {
    if (infected[u]) {
        candidates.push_back(dist);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, dist + 1, candidates, max_dist);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    string s;
    cin >> s;
    
    for (int i = 0; i < n; i++) {
        infected[i + 1] = s[i] - '0';
    }
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int Q;
    cin >> Q;
    
    while (Q--) {
        int nights;
        cin >> nights;
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (infected[i]) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```
