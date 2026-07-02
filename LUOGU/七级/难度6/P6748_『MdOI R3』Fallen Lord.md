# 『MdOI R3』Fallen Lord

## 题目描述
树上n-1条边赋值[1,m]，每个节点有忍耐度a_i。如果与节点相连边的中位数>a_i则谋反。求最大总战斗力。

## 输入格式
第一行n m，第二行a_i，接下来n-1行u_i v_i。

## 输出格式
最大总战斗力或-1。

## 样例
输入：
```
7 100
50 25 25 12 12 12 12
1 2
1 3
2 4
2 5
3 6
3 7
```
输出：
```
148
```

## 解题思路

### 问题分析
- 树形DP
- 需要保证中位数<=a_i

### 核心思路
- 贪心给边赋值，尽量用大值
- 对每个节点，收集子树信息

### 复杂度分析
- 时间复杂度：O(n)
- 空间复杂度：O(n)

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
int a[MAXN];
int n, m;
long long ans = 0;

void dfs(int u, int fa) {
    vector<int> vals;
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs(v, u);
        vals.push_back(a[v]);
    }
    
    if (vals.empty()) return;
    
    sort(vals.begin(), vals.end());
    int mid = vals[vals.size() / 2];
    
    if (mid > a[u]) {
        cout << "-1\n";
        exit(0);
    }
    
    for (int x : vals) {
        ans += min(x, a[u]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, 0);
    cout << ans << "\n";
    
    return 0;
}
```
