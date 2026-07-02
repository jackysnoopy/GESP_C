#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
int a[MAXN];
int n, m;
long long ans = 0;

void dfs(int u, int fa) {
    vector<int> vals;
    for (int v : adj[u]) {
        if (v == fa) continue;
        dfs(v, u);
        vals.push_back(a[v]);
    }
    
    if (vals.empty()) return;
    
    sort(vals.begin(), vals.end());
    int mid = vals[vals.size() / 2];
    
    if (mid > a[u]) {
        cout << "-1\n";
        exit(0);
    }
    
    for (int x : vals) {
        ans += min(x, a[u]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, 0);
    cout << ans << "\n";
    
    return 0;
}
