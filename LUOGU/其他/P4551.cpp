#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100005 * 31;
int trie[MAXN][2], tot = 1;

void insert(int x) {
    int p = 1;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (!trie[p][b]) trie[p][b] = ++tot;
        p = trie[p][b];
    }
}

int query(int x) {
    int p = 1, res = 0;
    for (int i = 30; i >= 0; i--) {
        int b = (x >> i) & 1;
        if (trie[p][b ^ 1]) { res |= (1 << i); p = trie[p][b ^ 1]; }
        else p = trie[p][b];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<vector<pair<int,int>>> g(n);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    vector<int> xor_val(n, 0);
    function<void(int,int)> dfs = [&](int u, int p) {
        for (auto [v, w] : g[u]) {
            if (v == p) continue;
            xor_val[v] = xor_val[u] ^ w;
            dfs(v, u);
        }
    };
    dfs(0, -1);
    
    for (int x : xor_val) insert(x);
    int ans = 0;
    for (int x : xor_val) ans = max(ans, query(x));
    cout << ans << "\n";
    return 0;
}