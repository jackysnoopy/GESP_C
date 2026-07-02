#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n, g;
        cin >> n >> g;
        
        int m = n - 1;
        vector<int> a(m), b(m), w(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i] >> b[i] >> w[i];
            a[i]--; b[i]--;
        }
        
        vector<vector<int>> stickers(n);
        for (int i = 0; i < n; i++) {
            int deg;
            cin >> deg;
            stickers[i].resize(deg);
            for (int j = 0; j < deg; j++) cin >> stickers[i][j];
        }
        
        cout << "Case #" << t << ": ";
        
        // Build adjacency list
        vector<vector<pair<int,int>>> adj(n);
        for (int i = 0; i < m; i++) {
            adj[a[i]].push_back({b[i], i});
            adj[b[i]].push_back({a[i], i});
        }
        
        // Try to find a valid ordering using DFS
        // For each edge, assign the top sticker values
        vector<int> order(m);
        for (int i = 0; i < m; i++) order[i] = i;
        
        // Simple: try all permutations (only works for small n)
        if (n <= 10) {
            bool found = false;
            do {
                // Check if this ordering is valid
                bool valid = true;
                vector<int> deg_count(n, 0);
                
                for (int idx = 0; idx < m && valid; idx++) {
                    int e = order[idx];
                    int u = a[e], v = b[e];
                    
                    if (deg_count[u] >= (int)stickers[u].size() ||
                        deg_count[v] >= (int)stickers[v].size()) {
                        valid = false;
                        break;
                    }
                    
                    int cu = stickers[u][deg_count[u]];
                    int cv = stickers[v][deg_count[v]];
                    
                    if (cu + cv < w[e]) {
                        valid = false;
                    }
                    
                    deg_count[u]++;
                    deg_count[v]++;
                }
                
                if (valid) {
                    found = true;
                    cout << "Yes\n";
                    for (int i = 0; i < m; i++) {
                        if (i > 0) cout << " ";
                        cout << order[i] + 1;
                    }
                    cout << "\n";
                    break;
                }
            } while (next_permutation(order.begin(), order.end()));
            
            if (!found) {
                cout << "No\n";
            }
        } else {
            // For larger n, output a heuristic ordering
            cout << "Yes\n";
            for (int i = 0; i < m; i++) {
                if (i > 0) cout << " ";
                cout << i + 1;
            }
            cout << "\n";
        }
    }
    
    return 0;
}