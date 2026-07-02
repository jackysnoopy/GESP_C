#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;
const int MAXN = 105;
const int MAXM = 10005;

struct Edge {
    int u, v, w;
};

int n, m, r;
Edge edges[MAXM];
int pre[MAXN]; // predecessor of each node
int id[MAXN]; // new id after contraction
int vis[MAXN]; // visit flag for contraction
int inc[MAXN]; // incoming edge weight

long long edmonds() {
    long long res = 0;
    while (true) {
        // Step 1: find minimum incoming edge for each node
        for (int i = 1; i <= n; i++) inc[i] = INF, pre[i] = -1;
        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            if (u != v && w < inc[v]) {
                inc[v] = w;
                pre[v] = u;
            }
        }
        inc[r] = 0;
        pre[r] = r;
        // Check if all nodes have incoming edges
        for (int i = 1; i <= n; i++) {
            if (i == r) continue;
            if (inc[i] == INF) return -1; // unreachable
        }
        // Step 2: find cycles
        int cnt = 0;
        for (int i = 1; i <= n; i++) id[i] = vis[i] = 0;
        for (int i = 1; i <= n; i++) {
            res += inc[i];
            int v = i;
            while (vis[v] != i && id[v] == 0 && v != r) {
                vis[v] = i;
                v = pre[v];
            }
            if (v != r && id[v] == 0) {
                // Found a cycle
                cnt++;
                int u = pre[v];
                while (u != v) {
                    id[u] = cnt;
                    u = pre[u];
                }
                id[v] = cnt;
            }
        }
        if (cnt == 0) break; // no cycles
        // Assign new ids to non-cycle nodes
        for (int i = 1; i <= n; i++)
            if (id[i] == 0) id[i] = ++cnt;
        // Step 3: contract cycles and adjust edge weights
        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v, w = edges[i].w;
            edges[i].u = id[u];
            edges[i].v = id[v];
            if (id[u] != id[v]) edges[i].w = w - inc[v];
        }
        n = cnt;
        r = id[r];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m >> r;
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    long long ans = edmonds();
    cout << ans << "\n";
    return 0;
}
