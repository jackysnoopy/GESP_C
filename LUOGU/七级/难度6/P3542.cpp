#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> deg(n + 1, 0);
    for (int i = 1; i <= n; i++) deg[i] = adj[i].size();
    
    int leaf = 0;
    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) leaf++;
    }
    
    cout << leaf << endl;
    return 0;
}
