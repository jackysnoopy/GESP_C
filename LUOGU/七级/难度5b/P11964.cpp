#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<vector<int>> ans(n + 1, vector<int>(k + 1));

    for (int start = 1; start <= n; start++) {
        // For each step, track which nodes are reachable in exactly that many steps.
        // Use visited only to deduplicate within a single step.
        vector<int> cur;
        cur.push_back(start);

        for (int step = 1; step <= k; step++) {
            vector<bool> visited(n + 1, false);
            vector<int> next;
            for (int u : cur) {
                for (int v : g[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        next.push_back(v);
                    }
                }
            }
            cur = next;
            ans[start][step] = (int)cur.size();
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j > 1) cout << " ";
            cout << ans[i][j];
        }
        cout << "\n";
    }
    return 0;
}
