#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<vector<pair<int, long long>>> g(n + 1);
    long long sum = 0;
    for (int i = 1; i < n; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        sum += w;
    }
    
    long long maxDist = 0;
    function<void(int,int,long long)> dfs = [&](int u, int fa, long long dist) {
        maxDist = max(maxDist, dist);
        for (auto [v, w] : g[u]) {
            if (v == fa) continue;
            dfs(v, u, dist + w);
        }
    };
    dfs(1, 0, 0);
    
    cout << 2 * sum - maxDist << "\n";
    return 0;
}
