#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
bool edge_exists[MAXN];
int n, m, q;

bool has_path(int u, int target) {
    if (u == target) return true;
    
    for (int v : adj[u]) {
        if (edge_exists[v] && has_path(v, target)) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> q;
    
    vector<pair<int, int>> edges(m + 1);
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        adj[u].push_back(i);
        edge_exists[i] = true;
    }
    
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        
        if (!edge_exists[x]) {
            cout << 0 << "\n";
            continue;
        }
        
        // Check if removing edge x still has path
        edge_exists[x] = false;
        
        if (has_path(1, n)) {
            cout << 1 << "\n";
        } else {
            edge_exists[x] = true;
            cout << 0 << "\n";
        }
    }
    
    return 0;
}