#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> ans;
vector<bool> vis;
int edge_cnt;
int del_u, del_v;

void dfs(int u) {
    vis[u] = true;
    ans.push_back(u);
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (u == del_u && v == del_v) continue;
            if (u == del_v && v == del_u) continue;
            dfs(v);
            ans.push_back(u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adj.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Sort adjacency lists for lexicographic order
    for (int i = 1; i <= n; i++)
        sort(adj[i].begin(), adj[i].end());

    if (m == n - 1) {
        // Tree: DFS from 1, always visit smallest neighbor first
        vis.assign(n + 1, false);
        dfs(1);
        for (int i = 0; i < (int)ans.size(); i++) {
            if (i > 0) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    } else {
        // One extra edge: try removing each edge on the cycle
        // Find the cycle first
        vis.assign(n + 1, false);
        vector<int> parent(n + 1, 0);
        int cycle_u = -1, cycle_v = -1;

        // DFS to find cycle
        function<void(int)> find_cycle = [&](int u) {
            vis[u] = true;
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                if (vis[v]) {
                    cycle_u = u;
                    cycle_v = v;
                    return;
                }
                parent[v] = u;
                find_cycle(v);
                if (cycle_u != -1) return;
            }
        };
        find_cycle(1);

        // Try removing each edge on the cycle
        vector<pair<int, int>> cycle_edges;
        int v = cycle_u;
        while (v != cycle_v) {
            cycle_edges.push_back({v, parent[v]});
            v = parent[v];
        }
        cycle_edges.push_back({cycle_u, cycle_v});

        vector<int> best_ans;
        for (int ci = 0; ci < (int)cycle_edges.size(); ci++) {
            int eu = cycle_edges[ci].first, ev = cycle_edges[ci].second;
            del_u = eu;
            del_v = ev;
            ans.clear();
            vis.assign(n + 1, false);
            dfs(1);
            if (best_ans.empty() || ans < best_ans)
                best_ans = ans;
        }

        for (int i = 0; i < (int)best_ans.size(); i++) {
            if (i > 0) cout << " ";
            cout << best_ans[i];
        }
        cout << "\n";
    }
    return 0;
}
