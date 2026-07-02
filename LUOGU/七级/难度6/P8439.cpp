#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1000005;
vector<int> adj[MAXN];
bool visited[MAXN];
int n, k;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Count connected components and edges
    int components = 0;
    long long total_edges = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            components++;
            queue<int> q;
            q.push(i);
            visited[i] = true;
            int node_count = 0;
            int edge_count = 0;
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                node_count++;
                edge_count += adj[u].size();
                
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            
            total_edges += edge_count / 2;
        }
    }
    
    // Each component with n nodes has n edges (given property)
    // We need to remove edges to get k stars
    int need = k;
    int ans = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // This component has size nodes and size edges
            // To get stars from it, we need to remove edges
        }
    }
    
    cout << max(0, k - components) << endl;
    
    return 0;
}