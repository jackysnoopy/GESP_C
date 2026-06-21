#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> indeg(n+1, 0);
        vector<vector<int>> adj(n+1);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[v].push_back(u);
            indeg[u]++;
        }
        priority_queue<int> pq;
        for (int i = 1; i <= n; i++)
            if (indeg[i] == 0) pq.push(i);
        vector<int> order;
        while (!pq.empty()) {
            int u = pq.top(); pq.pop();
            order.push_back(u);
            for (int v : adj[u]) {
                indeg[v]--;
                if (indeg[v] == 0) pq.push(v);
            }
        }
        if ((int)order.size() != n) {
            cout << "Impossible!\n";
            continue;
        }
        reverse(order.begin(), order.end());
        for (int i = 0; i < n; i++)
            cout << order[i] << " \n"[i==n-1];
    }
    return 0;
}
