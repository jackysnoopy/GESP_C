#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXN];
int dp[MAXN];

void dfs1(int u, int p) {
    parent[u] = p;
    depth[u] = depth[p] + 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs1(v, u);
        }
    }
}

void dfs2(int u, int p, int k) {
    dp[u] = 0;
    for (int v : adj[u]) {
        if (v != p) {
            dfs2(v, u, k);
            dp[u] = max(dp[u], dp[v] + 1);
        }
    }
    if (dp[u] == k) {
        dp[u] = -1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    depth[0] = -1;
    dfs1(1, 0);
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (dp[i] == k) {
            ans++;
        }
    }
    
    cout << max(1, ans) << "\n";
    
    return 0;
}