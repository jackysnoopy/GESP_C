#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nc, cas = 0;
    while (cin >> nc && nc) {
        map<int, int> id;
        vector<vector<int>> adj(nc);
        int idx = 0;

        for (int i = 0; i < nc; i++) {
            int a, b; cin >> a >> b;
            if (!id.count(a)) id[a] = idx++;
            if (!id.count(b)) id[b] = idx++;
            adj[id[a]].push_back(id[b]);
            adj[id[b]].push_back(id[a]);
        }

        int start, ttl;
        while (cin >> start >> ttl && (start || ttl)) {
            if (!id.count(start)) {
                cout << idx << " node(s) not reachable from node " << start << " with TTL = " << ttl << ".\n";
                continue;
            }

            vector<int> dist(idx, -1);
            queue<int> q;
            int sid = id[start];
            dist[sid] = 0;
            q.push(sid);

            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (dist[u] >= ttl) continue;
                for (int v : adj[u]) {
                    if (dist[v] < 0) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }

            int unreachable = 0;
            for (int i = 0; i < idx; i++)
                if (dist[i] < 0) unreachable++;

            cout << unreachable << " node(s) not reachable from node " << start << " with TTL = " << ttl << ".\n";
        }
    }
    return 0;
}
