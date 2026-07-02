#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<pair<int, char>>> adj(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }
        
        vector<int> result(n + 1, -1);
        result[1] = 0;
        
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << result[i];
        }
        cout << "\n";
    }
    
    return 0;
}