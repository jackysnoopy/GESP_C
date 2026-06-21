#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 50005;
const int LOG = 16;

int n, m;
vector<pair<int,int>> adj[MAXN];
int army[MAXN];
int depth[MAXN];
int parent[MAXN][LOG];
int dist_to_root[MAXN];
int up_dist[MAXN][LOG];

void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u][0] = p;
    for (int k = 1; k < LOG; k++) parent[u][k] = parent[parent[u][k-1]][k-1];
    for (auto& edge : adj[u]) {
        int v = edge.first, w = edge.second;
        if (v != p) {
            up_dist[v][0] = w;
            for (int k = 1; k < LOG; k++)
                up_dist[v][k] = up_dist[v][k-1] + up_dist[parent[v][k-1]][k-1];
            dist_to_root[v] = dist_to_root[u] + w;
            dfs(v, u, d + 1);
        }
    }
}

bool check(long long T) {
    vector<int> covered(n + 1, 0);
    vector<pair<int,int>> available;
    for (int i = 0; i < m; i++) {
        int a = army[i];
        int cur = a;
        long long remaining = T;
        for (int k = LOG - 1; k >= 0; k--) {
            if (parent[cur][k] > 0 && up_dist[cur][k] <= remaining) {
                remaining -= up_dist[cur][k];
                cur = parent[cur][k];
            }
        }
        if (cur == 1) {
            available.push_back({(int)remaining, cur});
        } else if (parent[cur][0] == 1) {
            covered[cur] = 1;
        } else {
            covered[cur] = 1;
        }
    }
    vector<int> uncovered;
    for (auto& edge : adj[1]) {
        int v = edge.first;
        if (!covered[v]) uncovered.push_back(v);
    }
    if (uncovered.empty()) return true;
    sort(available.begin(), available.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.first > b.first;
    });
    sort(uncovered.begin(), uncovered.end(), [](int a, int b) {
        return dist_to_root[a] > dist_to_root[b];
    });
    int j = 0;
    for (int i = 0; i < (int)uncovered.size(); i++) {
        int v = uncovered[i];
        int need = dist_to_root[v];
        while (j < (int)available.size() && available[j].first < need) j++;
        if (j >= (int)available.size()) return false;
        j++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    cin >> m;
    for (int i = 0; i < m; i++) cin >> army[i];
    memset(parent, 0, sizeof(parent));
    memset(up_dist, 0, sizeof(up_dist));
    dist_to_root[1] = 0;
    dfs(1, 0, 0);
    long long lo = 0, hi = (long long)1e18;
    if (!check(hi)) { cout << -1 << "\n"; return 0; }
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
