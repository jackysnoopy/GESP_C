#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m, timer_cnt;
int low[10005], disc[10005];
vector<int> adj[10005];
vector<pair<int, int>> bridges;

void dfs(int u, int parent) {
    disc[u] = low[u] = ++timer_cnt;
    for (int v : adj[u]) {
        if (!disc[v]) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > disc[u]) {
                bridges.push_back({min(u, v), max(u, v)});
            }
        } else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> n >> m;
        for (int i = 1; i <= n; i++) adj[i].clear();
        bridges.clear();
        timer_cnt = 0;
        memset(low, 0, sizeof(low));
        memset(disc, 0, sizeof(disc));

        for (int i = 0; i < m; i++) {
            int u, v;
            char c1, c2;
            cin >> u >> c1 >> v >> c2;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= n; i++) {
            if (!disc[i]) dfs(i, -1);
        }

        sort(bridges.begin(), bridges.end());

        cout << "Case " << t << ":" << endl;
        cout << bridges.size() << " critical links" << endl;
        for (auto &p : bridges) {
            cout << p.first << " - " << p.second << endl;
        }
        cout << endl;
    }
    return 0;
}
