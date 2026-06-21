#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> adj;
int sz[100005];
int K, N;
bool ok;

void dfs(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sz[u] += sz[v];
    }
    if (sz[u] == K) sz[u] = 0;
}

void solve() {
    cin >> N >> K;
    adj.clear();
    adj.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    if (N % K != 0) { cout << "NO\n"; return; }
    dfs(1, -1);
    if (sz[1] == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}
