#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int n, q;
long long ans = 0;

void dfs(int u, int parent, int depth) {
    for (int v : adj[u]) {
        if (v != parent) {
            ans += abs(depth - (depth + 1));
            dfs(v, u, depth + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 简单实现：按深度分配标号
    dfs(1, -1, 0);
    cout << ans << "\n";
    
    cin >> q;
    while (q--) {
        int f;
        cin >> f;
        n++;
        adj[f].push_back(n);
        adj[n].push_back(f);
        
        // 重新计算
        ans = 0;
        dfs(1, -1, 0);
        cout << ans << "\n";
    }
    
    return 0;
}