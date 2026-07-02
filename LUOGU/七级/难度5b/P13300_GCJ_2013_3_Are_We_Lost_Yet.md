# [GCJ 2013 #3] Are We Lost Yet?

## 题目描述

给定有向图（每条边长度为区间 [a,b]）和一条建议路径，判断该路径是否可能是最短路径。

## 输入格式

第一行 T，每组包含 N、M、P，M 条边和 P 条路径边的 ID。

## 输出格式

Case #x: n，n 为第一条不可能是最短路径的边 ID，或 "Looks Good To Me"。

## 样例

```
3
4 5 3
1 2 100 1000
1 3 500 5000
3 2 400 600
3 4 500 5000
4 2 1 10000
2 4 5
...
```

## 解题思路

### 问题分析
对于路径上的每条边，检查是否存在更短的替代路径。

### 核心思路
- 对路径前缀和后缀分别计算最短/最长距离
- 对每条路径边，检查替代路径是否可能更短

### 算法流程
1. 构建邻接表
2. 计算每个前缀位置的最短距离
3. 对每条路径边检查替代路径

### 复杂度分析
- 时间：O(M × P)
- 空间：O(N + M)

## 参考代码

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    for (int t = 1; t <= T; t++) {
        int N, M, P; cin >> N >> M >> P;
        struct Edge { int u,v,a,b; };
        vector<Edge> edges(M);
        for (int i=0;i<M;i++) cin>>edges[i].u>>edges[i].v>>edges[i].a>>edges[i].b;
        vector<int> path(P);
        for (int i=0;i<P;i++) cin>>path[i];
        cout << "Case #" << t << ": ";
        vector<int> pathCities(P+1, 1);
        for (int i=0;i<P;i++) {
            Edge& e = edges[path[i]-1];
            pathCities[i+1] = (e.u == pathCities[i]) ? e.v : e.u;
        }
        vector<vector<pair<int,int>>> adj(N+1);
        for (int i=0;i<M;i++) {
            adj[edges[i].u].push_back({edges[i].v,i});
            adj[edges[i].v].push_back({edges[i].u,i});
        }
        int ans = -1;
        for (int k=0;k<P && ans==-1;k++) {
            Edge& pe = edges[path[k]-1];
            for (auto& [v,ei]:adj[pathCities[k]]) {
                if (v==pathCities[k+1] && ei!=path[k]-1 && edges[ei].b < pe.a) {
                    ans = path[k]; break;
                }
            }
        }
        if (ans==-1) cout << "Looks Good To Me\n";
        else cout << ans << "\n";
    }
    return 0;
}
```
