#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> children(n + 1);
        vector<int> par(n + 1, 0), dep(n + 1, 0);
        for (int i = 2; i <= n; i++) {
            cin >> par[i];
            children[par[i]].push_back(i);
        }
        function<void(int, int)> compute_dep = [&](int u, int d) {
            dep[u] = d;
            for (int v : children[u]) compute_dep(v, d + 1);
        };
        compute_dep(1, 0);
        int maxdep = 0;
        for (int i = 1; i <= n; i++) maxdep = max(maxdep, dep[i]);
        int d = min(maxdep, k - 1);
        int endpoint = 1;
        for (int i = 1; i <= n; i++) {
            if (dep[i] == d) { endpoint = i; break; }
        }
        vector<int> path;
        { int cur = endpoint; while (cur != 0) { path.push_back(cur); cur = par[cur]; } reverse(path.begin(), path.end()); }
        vector<bool> on_path(n + 1, false);
        for (int node : path) on_path[node] = true;
        vector<bool> selected(n + 1, false);
        vector<int> bfs_queue;
        for (int node : path) { selected[node] = true; bfs_queue.push_back(node); }
        int count = path.size();
        int qi = 0;
        while (count < k && qi < (int)bfs_queue.size()) {
            int u = bfs_queue[qi++];
            for (int v : children[u]) {
                if (!selected[v]) { selected[v] = true; count++; bfs_queue.push_back(v); if (count >= k) break; }
            }
        }
        vector<int> walk;
        function<void(int)> dfs_walk = [&](int u) {
            walk.push_back(u);
            int path_child = -1;
            if (on_path[u] && u != endpoint) {
                for (int v : children[u]) { if (selected[v] && on_path[v]) { path_child = v; break; } }
            }
            for (int v : children[u]) {
                if (!selected[v] || v == path_child) continue;
                dfs_walk(v); walk.push_back(u);
            }
            if (path_child != -1) dfs_walk(path_child);
        };
        dfs_walk(1);
        cout << walk.size() - 1 << "\n";
        for (int i = 0; i < (int)walk.size(); i++) cout << walk[i] << (i < (int)walk.size() - 1 ? " " : "\n");
    }
    return 0;
}
