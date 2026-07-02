# 「KDOI-04」挑战 NPC Ⅲ

## 题目描述
给出一个含有 $n$ 个顶点，$m$ 条边的无向图 $G$，求 $G$ 中大小恰好为 $n-k$ 的独立集的数量。由于答案可能很大，请将其对 $998~244~353$ 取模。

## 输入格式
第一行一个正整数 $T$，表示测试数据组数。

对于每组测试数据，第一行三个正整数 $n,m,k$。

接下来 $m$ 行，每行两个正整数 $u,v$ 表示一条边。

## 输出格式
对于每组测试数据，输出一行一个正整数，表示符合要求的独立集数量。

## 样例
### 样例1
输入:
```
3
4 6 3
1 2
1 3
1 4
2 3
2 4
3 4
4 6 2
1 2
1 3
1 4
2 3
2 4
3 4
8 12 5
1 2
1 3
2 3
3 4
4 5
5 6
6 7
7 8
1 8
2 8
3 8
4 8
```
输出:
```
0
4
8
```

## 提示
- 时间限制：1000ms
- 内存限制：262144KB

## 解题思路

### 问题分析
需要计算图中大小为 $n-k$ 的独立集数量。

### 核心思路
1. 使用动态规划或容斥原理
2. 枚举独立集的组成

### 算法流程
1. 使用位运算枚举所有子集
2. 检查是否为独立集
3. 统计满足条件的数量

### 复杂度分析
- 时间复杂度：$O(2^n \cdot n)$
- 空间复杂度：$O(2^n)$

## 参考代码
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
const int MAXN = 105;
int n, m, k;
vector<int> adj[MAXN];
bool edge[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m >> k;
        
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            for (int j = 1; j <= n; j++) {
                edge[i][j] = false;
            }
        }
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            edge[u][v] = edge[v][u] = true;
        }
        
        vector<int> dp(1 << n, 0);
        dp[0] = 1;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == 0) continue;
            
            int next = -1;
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    next = i;
                    break;
                }
            }
            
            if (next == -1) continue;
            
            bool can_add = true;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    if (edge[i + 1][next + 1]) {
                        can_add = false;
                        break;
                    }
                }
            }
            
            if (can_add) {
                dp[mask | (1 << next)] = (dp[mask | (1 << next)] + dp[mask]) % MOD;
            }
            
            dp[mask | (1 << next)] = (dp[mask | (1 << next)] + dp[mask]) % MOD;
        }
        
        long long ans = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            if (__builtin_popcount(mask) == n - k) {
                ans = (ans + dp[mask]) % MOD;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
```