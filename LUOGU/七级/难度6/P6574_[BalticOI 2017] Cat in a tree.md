# [BalticOI 2017] Cat in a tree

## 题目描述
树上选最多节点，使任意两节点距离>=d。

## 输入格式
第一行n d，接下来n-1行每行x_i表示节点i连向x_i。

## 输出格式
最多节点数。

## 样例
输入：
```
4 3
0
0
1
```
输出：
```
2
```

## 解题思路

### 问题分析
- 贪心+树形DP
- 对每个节点，收集子树返回的距离信息

### 核心思路
- 用multiset维护子树距离
- 贪心配对，使距离>=d

### 复杂度分析
- 时间复杂度：O(n log n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int n, d;
int ans = 0;

multiset<int> dfs(int u, int fa) {
    multiset<int> s;
    s.insert(0);
    
    for (int v : adj[u]) {
        if (v == fa) continue;
        auto cs = dfs(v, u);
        for (int x : cs) s.insert(x + 1);
    }
    
    while (s.size() > 1) {
        auto it = s.end();
        --it;
        int mx = *it;
        s.erase(it);
        
        auto lb = s.lower_bound(d - mx);
        if (lb != s.end()) {
            s.erase(lb);
            ans++;
        } else {
            s.insert(mx);
            break;
        }
    }
    
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> d;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    
    dfs(0, -1);
    cout << ans << "\n";
    return 0;
}
```
