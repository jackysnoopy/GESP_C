#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

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
    
    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() > 2) {
            ans = adj[i].size();
            break;
        }
    }
    
    cout << ans << endl;
    return 0;
}