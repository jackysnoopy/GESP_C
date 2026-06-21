#include <iostream>
#include <vector>
#include <queue>
using namespace std;

pair<int, vector<int>> bfs(int n, const vector<vector<int>>& g, int start) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int farthest = start;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthest]) farthest = v;
            }
        }
    }
    return {farthest, dist};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) cin >> a[i];
        vector<vector<int>> g(n + 1);
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        
        int first = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) { first = i; break; }
        }
        if (first == -1) { cout << "Yes\n"; continue; }
        
        auto r1 = bfs(n, g, first);
        int u = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1 && (u == -1 || r1.second[i] > r1.second[u])) u = i;
        }
        
        auto r2 = bfs(n, g, u);
        int v = -1;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1 && (v == -1 || r2.second[i] > r2.second[v])) v = i;
        }
        
        auto r3 = bfs(n, g, v);
        bool ok = true;
        for (int i = 1; i <= n; i++) {
            if (a[i] == 1) {
                if (r2.second[i] + r3.second[i] != r2.second[v]) { ok = false; break; }
            }
        }
        cout << (ok ? "Yes" : "No") << "\n";
    }
    return 0;
}
