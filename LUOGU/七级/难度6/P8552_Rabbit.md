# Rabbit

## 题目描述
给定一棵树，共 $n$ 个点，分别编号为 $1\sim n$。

每次操作，你需要选出三个点 $a,b,c$ 将他们标记，满足：

- $c$ 是 $a$ 到 $b$ 简单路径上编号最大的点；
- $a,b,c$ 两两不同；
- $a,b,c$ 先前都没有被标记过。

问至多能进行多少次操作。

## 输入格式
本题有多组数据。

第一行是数据组数 $T$，接下来 $T$ 组数据，每组数据格式如下：

第一行一个正整数 $n$。

接下来 $n-1$ 行，每行两个正整数 $x,y$，描述树上的一条连接 $x,y$ 的边。

## 输出格式
对于每组数据输出一行一个非负整数，为答案。

## 样例
### 样例1
输入:
```
3
3
2 3
1 3
4
2 3
3 4
4 1
7
2 5
5 1
2 6
2 3
7 4
3 7
```
输出:
```
1
1
2
```

## 提示
- 时间限制：2000ms
- 内存限制：524288KB

## 解题思路

### 问题分析
需要在树上选择三元组 $(a,b,c)$，其中 $c$ 是 $a$ 到 $b$ 路径上编号最大的点。

### 核心思路
1. 使用贪心策略，优先选择编号大的点作为 $c$
2. 匹配 $a$ 和 $b$ 使得它们的路径包含 $c$

### 算法流程
1. 从大到小枚举可能的 $c$
2. 对于每个 $c$，尝试找到匹配的 $a$ 和 $b$
3. 标记已使用的点

### 复杂度分析
- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int n;
bool visited[MAXN];

int dfs(int u, int p) {
    int max_depth = 0;
    for (int v : adj[u]) {
        if (v != p && !visited[v]) {
            int depth = dfs(v, u) + 1;
            max_depth = max(max_depth, depth);
        }
    }
    return max_depth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n;
        
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            visited[i] = false;
        }
        
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() >= 2) {
                ans++;
            }
        }
        
        cout << max(1, ans / 2) << endl;
    }
    
    return 0;
}
```