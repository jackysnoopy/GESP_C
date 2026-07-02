#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, ans;
vector<int> adj[15];
bool used[15][15];

void dfs(int u, int cnt) {
    ans = max(ans, cnt);
    for (int v : adj[u]) {
        int a = min(u, v), b = max(u, v);
        if (!used[a][b]) {
            used[a][b] = true;
            dfs(v, cnt + 1);
            used[a][b] = false;
        }
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) adj[i].clear();
        memset(used, 0, sizeof(used));
        ans = 0;

        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= n; i++) {
            dfs(i, 0);
        }

        cout << ans << " roads" << endl;
    }
    return 0;
}
