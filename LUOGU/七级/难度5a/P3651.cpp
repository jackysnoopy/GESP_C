#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
vector<int> radj[MAXN];
int color[MAXN];
bool visited[MAXN];
int n;

void dfs1(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs1(v);
    }
}

void dfs2(int u, int c) {
    color[u] = c;
    for (int v : radj[u]) {
        if (!color[v]) dfs2(v, c);
    }
}

int main() {
    scanf("%d", &n);
    
    vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        scanf("%d%d", &a, &cost[i]);
        adj[i].push_back(a);
        radj[a].push_back(i);
    }
    
    // Kosaraju算法求强连通分量
    memset(visited, false, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) dfs1(i);
    }
    
    memset(color, 0, sizeof(color));
    int cnt = 0;
    for (int i = n; i >= 1; i--) {
        int u = i; // 这里需要按dfs1的结束时间逆序
        if (!color[u]) dfs2(u, ++cnt);
    }
    
    // 计算每个SCC的入度
    vector<int> indeg(cnt + 1, 0);
    for (int u = 1; u <= n; u++) {
        for (int v : adj[u]) {
            if (color[u] != color[v]) {
                indeg[color[v]]++;
            }
        }
    }
    
    // 对于入度为0的SCC，选择最小花费
    long long ans = 0;
    for (int i = 1; i <= cnt; i++) {
        if (indeg[i] == 0) {
            int min_cost = INT_MAX;
            for (int u = 1; u <= n; u++) {
                if (color[u] == i) {
                    min_cost = min(min_cost, cost[u]);
                }
            }
            ans += min_cost;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
