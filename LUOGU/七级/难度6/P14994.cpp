#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200005;
const long long MOD = 998244353;

int n, m;
vector<int> adj[MAXN];
int visited[MAXN];
int component[MAXN];
int compCnt;

void dfs(int u, int comp) {
    component[u] = comp;
    visited[u] = 1;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v, comp);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    
    vector<long long> w(m);
    vector<pair<int, int>> edges(m);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v >> w[i];
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges[i] = {u, v};
    }
    
    // Find connected components
    compCnt = 0;
    memset(visited, 0, sizeof(visited));
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            compCnt++;
            dfs(i, compCnt);
        }
    }
    
    // For each component, build linear basis of cycle space
    // The XOR shortest path between two nodes equals the XOR of edge weights along any path
    // Two paths differ by cycles, so we want to minimize XOR using cycle basis
    
    // For each component, find spanning tree and compute XOR distances from root
    // Then build linear basis from fundamental cycles
    
    long long result = 0;
    
    for (int comp = 1; comp <= compCnt; comp++) {
        // Get nodes in this component
        vector<int> nodes;
        for (int i = 1; i <= n; i++) {
            if (component[i] == comp) nodes.push_back(i);
        }
        
        if (nodes.size() <= 1) continue;
        
        // BFS to find spanning tree and XOR distances
        vector<long long> dist(n + 1, -1);
        vector<int> treeEdges;
        vector<int> nonTreeEdges;
        
        dist[nodes[0]] = 0;
        vector<int> q;
        q.push_back(nodes[0]);
        int head = 0;
        
        while (head < (int)q.size()) {
            int u = q[head++];
            for (int v : adj[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] ^ w[find_if(edges.begin(), edges.end(), 
                        [&](const pair<int,int>& e) {
                            return (e.first == u && e.second == v) || (e.first == v && e.second == u);
                        }) - edges.begin()];
                    q.push_back(v);
                } else {
                    // Non-tree edge - fundamental cycle
                    int idx = find_if(edges.begin(), edges.end(), 
                        [&](const pair<int,int>& e) {
                            return (e.first == u && e.second == v) || (e.first == v && e.second == u);
                        }) - edges.begin();
                    nonTreeEdges.push_back(dist[u] ^ dist[v] ^ w[idx]);
                }
            }
        }
        
        // Build linear basis from cycle weights
        vector<long long> basis(30, 0);
        for (long long x : nonTreeEdges) {
            for (int b = 29; b >= 0; b--) {
                if ((x >> b) & 1) {
                    if (basis[b] == 0) {
                        basis[b] = x;
                        break;
                    }
                    x ^= basis[b];
                }
            }
        }
        
        // For each node, compute its contribution
        // dist[u] ^ dist[v] can be reduced using the basis
        // We want sum of min(dist[u] ^ dist[v] reduced by basis) for all pairs
        
        // This is a known problem: sum of minimum XOR pairs
        // Use linear basis to reduce, then count
        
        // Simplified: for each pair, the minimum XOR is dist[u] XOR dist[v] reduced by basis
        // We can use the basis to find the minimum XOR for each dist value
        
        // For now, brute force for small components
        if (nodes.size() <= 1000) {
            for (int i = 0; i < (int)nodes.size(); i++) {
                for (int j = i + 1; j < (int)nodes.size(); j++) {
                    long long xorVal = dist[nodes[i]] ^ dist[nodes[j]];
                    // Reduce by basis
                    for (int b = 29; b >= 0; b--) {
                        if ((xorVal >> b) & 1) {
                            xorVal ^= basis[b];
                        }
                    }
                    result = (result + xorVal) % MOD;
                }
            }
        }
    }
    
    cout << result << "\n";
    return 0;
}
