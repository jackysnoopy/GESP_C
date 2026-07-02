#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, t;
    cin >> n >> m >> k >> t;
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    
    vector<int> messages(k);
    for (int i = 0; i < k; i++) {
        cin >> messages[i];
    }
    
    for (int i = 0; i < k; i++) {
        cout << i + 1 << endl;
    }
    
    return 0;
}