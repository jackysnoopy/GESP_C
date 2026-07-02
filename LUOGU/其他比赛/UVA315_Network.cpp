#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 102;
vector<int> adj[MAXN];
bool vis[MAXN];
int low[MAXN], dfn[MAXN], timer_cnt;
int n, ans;

void dfs(int u, int parent) {
    vis[u] = true;
    low[u] = dfn[u] = timer_cnt++;
    int children = 0;
    bool isArticulation = false;
    for (int v : adj[u]) {
        if (!vis[v]) {
            children++;
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (parent == -1 && children > 1) isArticulation = true;
            if (parent != -1 && low[v] >= dfn[u]) isArticulation = true;
        } else if (v != parent) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (isArticulation) ans++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin >> n && n) {
        for (int i = 1; i <= n; i++) adj[i].clear();
        int u, v;
        while (cin >> u && u) {
            string line;
            getline(cin, line);
            for (int i = 1; i < (int)line.size(); i++) {
                if (line[i] >= '0' && line[i] <= '9') {
                    v = v * 10 + (line[i] - '0');
                } else {
                    if (v > 0) {
                        adj[u].push_back(v);
                        adj[v].push_back(u);
                        v = 0;
                    }
                }
            }
            if (v > 0) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
        memset(vis, false, sizeof(vis));
        memset(low, 0, sizeof(low));
        memset(dfn, 0, sizeof(dfn));
        timer_cnt = 0;
        ans = 0;
        dfs(1, -1);
        cout << ans << "\n";
    }
    return 0;
}
