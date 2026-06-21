#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<int> adj[100001];
int color[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) color[i] = -1;
    for (int i = 1; i <= n; i++) {
        if (color[i] != -1) continue;
        queue<int> q2;
        q2.push(i);
        color[i] = 0;
        while (!q2.empty()) {
            int u = q2.front(); q2.pop();
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = color[u]^1;
                    q2.push(v);
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        if (color[a] == color[b]) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
