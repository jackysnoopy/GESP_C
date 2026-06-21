#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN = 40005;
vector<int> adj[MAXN];
int match[MAXN];
bool vis[MAXN];
bool dfs(int u) {
    for (int v : adj[u]) {
        if (!vis[v]) {
            vis[v] = true;
            if (match[v] == 0 || dfs(match[v])) { match[v] = u; return true; }
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int m, n; cin >> m >> n;
        for (int i = 1; i <= m+n; i++) adj[i].clear();
        memset(match, 0, sizeof(match));
        for (int i = 1; i <= m; i++) {
            int k; cin >> k;
            for (int j = 0; j < k; j++) { int p; cin >> p; adj[m+p].push_back(i); }
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            memset(vis, 0, sizeof(vis));
            if (dfs(m+i)) ans++;
        }
        cout << (ans == n ? "YES" : "NO") << endl;
    }
    return 0;
}