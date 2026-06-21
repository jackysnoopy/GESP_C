#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> depth(n + 1, -1);
        vector<int> parent(n + 1, -1);
        depth[1] = 0;
        parent[1] = -1;

        vector<int> queue;
        queue.push_back(1);

        for (int i = 0; i < (int)queue.size(); i++) {
            int u = queue[i];
            for (int v : adj[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    parent[v] = u;
                    queue.push_back(v);
                }
            }
        }

        int ans = 0;
        for (int i = 2; i <= n; i++) {
            if (parent[i] != i - 1) ans++;
        }

        cout << ans << "\n";
    }

    return 0;
}
