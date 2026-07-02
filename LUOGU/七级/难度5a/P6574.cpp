#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, d;
    cin >> n >> d;
    
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        adj[i].push_back(x);
        adj[x].push_back(i);
    }
    
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() > 1) {
            ans = max(ans, (int)adj[i].size());
        }
    }
    
    cout << ans << endl;
    return 0;
}