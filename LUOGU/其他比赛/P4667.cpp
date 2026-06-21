#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<pair<int,int>>> adj;
vector<int> path;
int n, m;

void hierholzer(int u) {
    while (!adj[u].empty()) {
        auto [v, idx] = adj[u].back();
        adj[u].pop_back();
        for (auto& e : adj[v]) {
            if (e.second == idx) { e = adj[v].back(); adj[v].pop_back(); break; }
        }
        hierholzer(v);
    }
    path.push_back(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    adj.resize(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        deg[u]++; deg[v]++;
    }
    vector<int> odds;
    for (int i = 1; i <= n; ++i) if (deg[i] % 2 == 1) odds.push_back(i);
    if (odds.size() == 0) {
        for (int i = 1; i <= n; ++i) if (!adj[i].empty()) { hierholzer(i); break; }
    } else if (odds.size() == 2) {
        hierholzer(odds[0]);
    } else {
        cout << "No Euler path\n"; return 0;
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
