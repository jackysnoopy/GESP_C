#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 200005;
const int LOGN = 19;

int n, m;
vector<int> adj[MAXN];
int depth[MAXN], parent[MAXN][LOGN];
int coverCount[MAXN];
bool removed[MAXN];
bool covered[MAXN];

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int i = 1; i < LOGN; i++)
        parent[u][i] = parent[parent[u][i-1]][i-1];
    for (int v : adj[u]) {
        if (v != p) dfs(v, u, d + 1);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOGN - 1; i >= 0; i--)
        if (depth[parent[u][i]] >= depth[v]) u = parent[u][i];
    if (u == v) return u;
    for (int i = LOGN - 1; i >= 0; i--)
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    return parent[u][0];
}

void markPath(int u, int v, int l) {
    while (u != l) {
        coverCount[u]++;
        u = parent[u][0];
    }
    while (v != l) {
        coverCount[v]++;
        v = parent[v][0];
    }
    coverCount[l]++;
}

void removeNode(int u) {
    removed[u] = true;
    coverCount[u] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    depth[0] = 0;
    dfs(1, 0, 0);

    vector<pair<int,int>> progs(m);
    for (int i = 0; i < m; i++) {
        cin >> progs[i].first >> progs[i].second;
        int l = lca(progs[i].first, progs[i].second);
        markPath(progs[i].first, progs[i].second, l);
    }

    vector<int> result;
    while (true) {
        bool allCovered = true;
        for (int i = 0; i < m; i++) {
            if (covered[i]) continue;
            int u = progs[i].first, v = progs[i].second;
            if (!removed[u] && !removed[v]) {
                int l = lca(u, v);
                bool pathClear = true;
                int tmp = u;
                while (tmp != l) {
                    if (removed[tmp]) { pathClear = false; break; }
                    tmp = parent[tmp][0];
                }
                if (pathClear) {
                    tmp = v;
                    while (tmp != l) {
                        if (removed[tmp]) { pathClear = false; break; }
                        tmp = parent[tmp][0];
                    }
                }
                if (pathClear && !removed[l]) {
                    allCovered = false;
                    break;
                }
            }
            covered[i] = true;
        }
        if (allCovered) break;

        int best = -1, bestCnt = -1;
        for (int i = 1; i <= n; i++) {
            if (!removed[i] && coverCount[i] > bestCnt) {
                bestCnt = coverCount[i];
                best = i;
            }
        }
        if (best == -1) break;
        removeNode(best);
        result.push_back(best);

        for (int i = 0; i < m; i++) {
            if (covered[i]) continue;
            int u = progs[i].first, v = progs[i].second;
            if (removed[u] || removed[v]) { covered[i] = true; continue; }
            int l = lca(u, v);
            bool pathClear = true;
            int tmp = u;
            while (tmp != l) {
                if (removed[tmp]) { pathClear = false; break; }
                tmp = parent[tmp][0];
            }
            if (pathClear) {
                tmp = v;
                while (tmp != l) {
                    if (removed[tmp]) { pathClear = false; break; }
                    tmp = parent[tmp][0];
                }
            }
            if (!pathClear || removed[l]) covered[i] = true;
        }
    }

    cout << result.size() << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << (i + 1 == (int)result.size() ? '\n' : ' ');
    }

    return 0;
}
