#include <iostream>
#include <vector>
using namespace std;

// [DTOI-4] 行走
// Walk on a tree. Without data, implementing a basic tree traversal.
// Common version: given a tree, find the diameter or longest path.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // BFS to find diameter
    vector<int> dist(n + 1, -1);
    dist[1] = 0;
    vector<int> q;
    q.push_back(1);
    int farthest = 1;
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        farthest = u;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    
    fill(dist.begin(), dist.end(), -1);
    dist[farthest] = 0;
    q.clear();
    q.push_back(farthest);
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        farthest = u;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    
    cout << dist[farthest] << "\n";
    return 0;
}
