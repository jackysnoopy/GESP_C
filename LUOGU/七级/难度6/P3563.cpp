#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 250005;
vector<int> adj[MAXN];
int sz[MAXN];
long long mx = 0;
void dfs(int u, int p) {
    sz[u] = 1;
    int mxchild = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
        mxchild = max(mxchild, sz[v]);
    }
    mxchild = max(mxchild, (int)adj[u].size() - mxchild);
    mx = max(mx, (long long)mxchild);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << mx << " " << (long long)n - 1 + mx << endl;
    return 0;
}