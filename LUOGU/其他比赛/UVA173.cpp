#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<pair<int,int>>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            adj[u].push_back(make_pair(v, w));
            adj[v].push_back(make_pair(u, w));
        }
        vector<int> dist(n + 1, -1);
        dist[1] = 0;
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push(make_pair(0, 1));
        while (!pq.empty()) {
            pair<int,int> cur = pq.top();
            pq.pop();
            int d = cur.first, u = cur.second;
            if (d > dist[u] && dist[u] != -1) continue;
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].first;
                int w = adj[u][i].second;
                if (dist[v] == -1 || d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        cout << dist[n] << endl;
    }
    return 0;
}
