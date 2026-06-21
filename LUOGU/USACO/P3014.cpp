#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int n, m;
long long dist[1<<16];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < n; i++) {
            if (u & (1<<i)) continue;
            int v = u | (1<<i);
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        int mask = 0;
        for (int j = 0; j < n; j++) {
            int x; cin >> x;
            if (x) mask |= (1<<j);
        }
        cout << dist[mask] << "\n";
    }
    return 0;
}
