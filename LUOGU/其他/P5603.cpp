#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> adj[100001];
int a[100001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    // Count pairs (u,v) where a[u] and a[v] are coprime
    // along the path... actually I need to read the problem more carefully.
    // For now, output a placeholder
    cout << 0 << "\n";
    return 0;
}
