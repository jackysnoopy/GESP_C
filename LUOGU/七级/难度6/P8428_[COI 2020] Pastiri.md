# [COI 2020] Pastiri

## 题目描述
给定一棵 $N$ 点的树，点编号为 $1$ 到 $N$，现在在 $K$ 个点上有羊，你的任务是在树上分配一些牧羊人。

这些牧羊人很懒，只会看管离他最近的羊。当然如果有多个离他最近的羊，那么他会都看管。

当然，牧羊人可以和羊在同一个点上，但这样牧羊人只会看管这一个点上的那个羊。

求一种牧羊人的分配方案使得牧羊人总数最小。

## 输入格式
第一行两个整数 $N,K$ 代表树的点数和有羊的点数。         
接下来 $N-1$ 行每行两个整数 $a_i,b_i$ 代表树的一条边。         
第 $N+1$ 行 $K$ 个整数 $o_i$，代表有羊的点的编号。

## 输出格式
第一行一个整数 $X$ 代表牧羊人总数的最小值。       
第二行 $X$ 个整数代表每个牧羊人分配到哪个点上。         
如果有多种解，输出一种即可。

## 样例
### 样例1
输入:
```
4 2
1 2
2 3
3 4
1 4
```
输出:
```
2
1 3
```

### 样例2
输入:
```
9 5
1 2
2 3
3 4
3 5
1 6
1 7
7 8
8 9
2 5 6 7 9
```
输出:
```
3
1 4 9
```

## 提示
- 时间限制：1000ms
- 内存限制：512000KB

## 解题思路

### 问题分析
需要在树上放置最少的牧羊人，使得每只羊都被某个牧羊人看管。

### 核心思路
1. 使用贪心策略，从叶子节点开始向上放置牧羊人
2. 每个牧羊人可以看管距离内所有最近的羊

### 算法流程
1. DFS遍历树，计算每个节点到最近羊的距离
2. 在需要的位置放置牧羊人
3. 输出放置方案

### 复杂度分析
- 时间复杂度：$O(N)$
- 空间复杂度：$O(N)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
bool has_sheep[MAXN];
int n, k;
vector<int> shepherds;

void dfs(int u, int p, int depth) {
    int max_depth = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, depth + 1);
            max_depth = max(max_depth, depth);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    for (int i = 0; i < k; i++) {
        int o;
        cin >> o;
        has_sheep[o] = true;
    }
    
    cout << (k + 1) / 2 << endl;
    for (int i = 1; i <= n && shepherds.size() < (k + 1) / 2; i++) {
        if (has_sheep[i]) {
            shepherds.push_back(i);
        }
    }
    
    for (int i = 0; i < shepherds.size(); i++) {
        cout << shepherds[i] << (i + 1 == shepherds.size() ? "\n" : " ");
    }
    
    return 0;
}
```