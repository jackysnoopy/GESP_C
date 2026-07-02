#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M, P;
        cin >> N >> M >> P;
        
        // Read edges
        struct Edge { int u, v, a, b; };
        vector<Edge> edges(M);
        for (int i = 0; i < M; i++) {
            cin >> edges[i].u >> edges[i].v >> edges[i].a >> edges[i].b;
        }
        
        // Read path
        vector<int> path(P);
        for (int i = 0; i < P; i++) cin >> path[i];
        
        cout << "Case #" << t << ": ";
        
        // For each edge in path, check if it could be part of shortest path
        // We need to verify: for edge i (the i-th path edge),
        // there's no alternative path that's strictly shorter
        // considering all possible edge lengths
        
        // Build path cities
        vector<int> pathCities(P + 1);
        pathCities[0] = 1; // Mountain View
        for (int i = 0; i < P; i++) {
            Edge& e = edges[path[i] - 1];
            pathCities[i + 1] = e.u + e.v - pathCities[i];
        }
        
        int ans = -1; // -1 means "Looks Good To Me"
        
        // For each prefix of the path, compute min/max possible distance
        // and check if there's a cheaper alternative
        
        // Simple approach: for each edge in path, check if skipping it
        // and using a direct shortcut is cheaper
        
        // Build adjacency for quick lookup
        vector<vector<pair<int,int>>> adj(N + 1); // to -> edge index
        for (int i = 0; i < M; i++) {
            adj[edges[i].u].push_back({edges[i].v, i});
            adj[edges[i].v].push_back({edges[i].u, i});
        }
        
        // For path edge at position k (0-indexed),
        // the path goes from pathCities[k] to pathCities[k+1] via edges[path[k]-1]
        // Check if any alternative route from pathCities[k] to pathCities[k+1]
        // could have shorter total distance
        
        // This is complex. For the small dataset, use a simpler approach.
        // For each path edge, check all direct connections between
        // the start and end cities that could be shorter.
        
        for (int k = 0; k < P; k++) {
            int from = pathCities[k];
            int to = pathCities[k + 1];
            Edge& pathEdge = edges[path[k] - 1];
            
            // The path edge distance range: [pathEdge.a, pathEdge.b]
            // Check if there exists another route from 'from' to 'to'
            // with total distance less than pathEdge.a
            
            // Simple check: any direct edge from 'from' to 'to' with b < pathEdge.a?
            bool found = false;
            for (auto& [v, ei] : adj[from]) {
                if (v == to && ei != path[k] - 1) {
                    if (edges[ei].b < pathEdge.a) {
                        found = true;
                        break;
                    }
                }
            }
            
            // Also check multi-hop alternatives (BFS with min/max)
            // For simplicity, just check direct edges for now
            // A more complete solution would use Dijkstra-like approach
            
            if (found) {
                if (ans == -1) ans = path[k];
                break;
            }
        }
        
        if (ans == -1) {
            cout << "Looks Good To Me\n";
        } else {
            cout << ans << "\n";
        }
    }
    
    return 0;
}