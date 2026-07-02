#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, G, root;
    cin >> n >> G >> root;
    
    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    
    int S, T;
    cin >> S >> T;
    
    long long ans = 0;
    for (int i = 0; i < S; i++) {
        int x, a;
        cin >> x >> a;
        ans += a;
    }
    for (int i = 0; i < T; i++) {
        int x, b;
        cin >> x >> b;
    }
    
    cout << ans << endl;
    return 0;
}