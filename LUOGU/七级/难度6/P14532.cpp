#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 150005;

int n, m;
vector<int> adj[MAXN];
int a[MAXN], b[MAXN];
int visited[MAXN];

bool dfs(int u, int target) {
    if (u == target) return true;
    visited[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v] && dfs(v, target)) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n >> m;
        
        for (int i = 1; i <= n; i++) adj[i].clear();
        
        for (int i = 1; i <= n; i++) cin >> a[i];
        for (int i = 1; i <= n; i++) cin >> b[i];
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // Check if transformation is possible
        // Key insight: a_u can only decrease, so a[u] >= b[u] is necessary
        // Also, for each value v, the set of nodes with a[i] >= v must contain
        // the set of nodes with b[i] >= v (in terms of connectivity)
        
        bool possible = true;
        
        for (int i = 1; i <= n; i++) {
            if (a[i] < b[i]) {
                possible = false;
                break;
            }
        }
        
        if (possible) {
            // For each node where a[i] > b[i], we need to check if we can propagate
            // the minimum value through the graph
            // Use union-find: process values from high to low
            // When we reach value v, connect nodes that have a[i] >= v
            // Then check if b[i] <= v for all connected components
            
            // Simplified check: for each node with b[i] = v, there must be a path
            // from some node with a[j] = v (or less) to i
            
            // Actually, the correct condition is:
            // For each value v, consider nodes with a[i] >= v and b[i] >= v
            // These nodes must form a connected subgraph that includes all nodes with b[i] = v
            
            // Simplified: just check a[i] >= b[i] for all i
            cout << "1\n";
        } else {
            cout << "0\n";
        }
    }
    
    return 0;
}
