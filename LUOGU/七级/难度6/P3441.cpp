#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 1000005;
vector<int> adj[MAXN];
int depth[MAXN], maxd[MAXN];
void dfs(int u, int p) {
    maxd[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        maxd[u] = max(maxd[u], maxd[v] + 1);
    }
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, l;
    cin >> n >> l;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (l == 0) { cout << 0 << endl; return 0; }
    if (l >= n - 1) { cout << n << endl; return 0; }
    dfs(1, 0);
    int diameter = 0;
    for (int i = 1; i <= n; i++) diameter = max(diameter, maxd[i]);
    cout << min(n, 2 * l + diameter + 1) << endl;
    return 0;
}