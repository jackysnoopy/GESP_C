#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<int>> g(n + 1);
    for (int i = 2; i <= n; i++) {
        int f;
        cin >> f;
        g[f].push_back(i);
    }
    
    vector<int> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    
    vector<ll> f(n + 1, 0);
    
    function<void(int)> dfs = [&](int u) {
        if (g[u].empty()) {
            f[u] = c[u];
            return;
        }
        ll sum = 0;
        for (int v : g[u]) {
            dfs(v);
            sum += f[v];
        }
        f[u] = min((ll)c[u], sum);
    };
    
    dfs(1);
    cout << f[1] << '\n';
    
    return 0;
}
