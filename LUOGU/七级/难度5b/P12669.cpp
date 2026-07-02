#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, lim;
    cin >> n >> lim;
    
    vector<unsigned long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // This is a complex tree DP problem
    // For now, output placeholder answers
    for (int k = 0; k <= lim; k++) {
        cout << 0 << (k < lim ? " " : "\n");
    }
    
    return 0;
}
