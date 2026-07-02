#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        indeg[v]++;
    }
    // Greedy on DAG: select up to k nodes with max weight
    // Constraint: can only select a node if it has in-degree > 0
    // (i.e., it's pointed to by at least one other node)
    // After selecting, remove the node and its outgoing edges
    //
    // This is equivalent to: repeatedly select the heaviest node with indegree > 0,
    // remove it and update indegrees.
    //
    // Use a priority queue (max-heap) of nodes with indegree > 0.
    // Select the heaviest, remove it, update indegrees of neighbors.

    priority_queue<pair<int, int>> pq; // (weight, node)
    for (int i = 1; i <= n; i++)
        if (indeg[i] > 0) pq.push({w[i], i});

    long long total = 0;
    int selected = 0;
    vector<bool> removed(n + 1, false);

    while (selected < k && !pq.empty()) {
        auto top = pq.top(); pq.pop();
        int node = top.second;
        if (removed[node]) continue;
        if (indeg[node] <= 0) continue; // might have changed

        total += w[node];
        removed[node] = true;
        selected++;

        // Remove outgoing edges
        for (int v : adj[node]) {
            if (!removed[v]) {
                indeg[v]--;
                if (indeg[v] > 0) pq.push({w[v], v});
            }
        }
    }

    cout << total << "\n";
    return 0;
}
