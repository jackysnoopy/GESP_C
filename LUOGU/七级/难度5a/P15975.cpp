#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

int n;
vector<int> a;
vector<vector<int>> adj;
vector<int> sub_gcd, par;

void dfs(int u, int p) {
    par[u] = p;
    sub_gcd[u] = a[u];
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        sub_gcd[u] = gcd(sub_gcd[u], sub_gcd[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    par.resize(n + 1);
    sub_gcd.resize(n + 1);
    dfs(1, 0);
    long long F = 0;
    for (int i = 1; i <= n; i++) F += sub_gcd[i];
    // Brute force: try moving each subtree to each possible location
    long long best = F;
    // For n <= 200, try all pairs
    if (n <= 200) {
        for (int q = 1; q <= n; q++) {
            for (int r = 1; r <= n; r++) {
                if (r == q || r == par[q]) continue;
                // Check if r is inside subtree of q
                bool inside = false;
                int tmp = r;
                while (tmp) { if (tmp == q) { inside = true; break; } tmp = par[tmp]; }
                if (inside) continue;
                // Simulate move: disconnect q from par[q], attach to r
                // Recompute GCDs along affected paths
                // This is O(n) per move
                vector<int> new_gcd(n + 1);
                // For nodes not on affected paths, GCD unchanged
                // Affected: path from root to par[q], and path from root to r
                // Simple approach: recompute all
                vector<vector<int>> adj2 = adj;
                // Remove edge q-par[q]
                auto& pv = adj2[par[q]];
                pv.erase(find(pv.begin(), pv.end(), q));
                auto& qv = adj2[q];
                qv.erase(find(qv.begin(), qv.end(), par[q]));
                // Add edge q-r
                adj2[r].push_back(q);
                adj2[q].push_back(r);
                // Recompute with new root=1
                function<int(int,int)> calc = [&](int u, int p) -> int {
                    int g = a[u];
                    for (int v : adj2[u]) if (v != p) g = gcd(g, calc(v, u));
                    return g;
                };
                long long newF = 0;
                for (int i = 1; i <= n; i++) newF += calc(i, 0);
                best = max(best, newF);
            }
        }
    }
    cout << best << "\n";
    return 0;
}
