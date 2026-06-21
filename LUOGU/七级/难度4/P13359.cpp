#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adj(n + 1);
        vector<int> indeg(n + 1, 0);

        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            adj[y].push_back(x);
            adj[z].push_back(x);
            indeg[x] += 2;
        }

        vector<int> val(n + 1, 1);
        queue<int> q;

        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) {
                indeg[v]--;
                if (indeg[v] == 0) q.push(v);
            }
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++) {
            if (indeg[i] == 0) {
                ans += val[i];
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
