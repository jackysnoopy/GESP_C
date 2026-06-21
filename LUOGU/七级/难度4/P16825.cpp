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

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        vector<vector<int>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        long long total = 0;
        for (int i = 0; i < n; i++) total += a[i];

        long long min_forest = total;
        for (int i = 0; i < n; i++) {
            if (adj[i].size() >= 2) {
                min_forest = min(min_forest, a[i]);
            }
        }

        cout << min_forest << "\n";
    }

    return 0;
}
