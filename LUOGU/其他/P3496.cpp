#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> adj[200001];
int color[200001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) color[i] = -1;
    for (int i = 1; i <= n; i++) {
        if (color[i] != -1) continue;
        queue<int> q;
        q.push(i);
        color[i] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u] ^ 1;
                    q.push(v);
                } else if (color[v] == color[u]) {
                    cout << "NIE\n";
                    return 0;
                }
            }
        }
    }
    cout << "TAK\n";
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) cout << "K\n";
        else cout << "S\n";
    }
    return 0;
}
