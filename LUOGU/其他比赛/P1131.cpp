#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500001;
vector<pair<int,int>> adj[MAXN];
long long depth[MAXN];
int maxDepth[MAXN];

void dfs(int u, int parent) {
    maxDepth[u] = 0;
    for (auto& e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == parent) continue;
        depth[v] = depth[u] + w;
        dfs(v, u);
        maxDepth[u] = max(maxDepth[u], maxDepth[v] + w);
    }
}

long long ans = 0;

void dfs2(int u, int parent) {
    for (auto& e : adj[u]) {
        int v = e.first, w = e.second;
        if (v == parent) continue;
        dfs2(v, u);
        // The max depth from v's subtree
        int mx = maxDepth[v] + w;
        // We need to increase this edge's weight so that all leaves from v are synced
        // with the max depth from u's perspective
        ans += maxDepth[u] - mx;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s;
    cin >> n >> s;
    for (int i = 0; i < n - 1; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        adj[a].push_back({b, t});
        adj[b].push_back({a, t});
    }
    depth[s] = 0;
    dfs(s, 0);
    dfs2(s, 0);
    cout << ans << "\n";
    return 0;
}
