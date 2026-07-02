#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

const int MAXN = 200005;
int parent[MAXN], rnk[MAXN];
vector<int> adj[MAXN];
int compRoot[MAXN];
int compNodes[MAXN];
bool inComp[MAXN];

int find(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i + 1;
    for (int v = 1; v <= n; v++) {
        for (int u : adj[v]) {
            if (u < v) unite(v, u);
        }
        compRoot[v] = find(v);
    }
    vector<int> compSize(n + 1, 0);
    for (int v = 1; v <= n; v++) {
        compSize[compRoot[v]]++;
    }
    vector<vector<int>> compMembers(n + 1);
    for (int v = 1; v <= n; v++) {
        compMembers[compRoot[v]].push_back(v);
    }
    while (q--) {
        int s, t;
        cin >> s >> t;
        if (s == t) {
            cout << 1 << "\n";
            continue;
        }
        if (compRoot[s] == compRoot[t] && t <= s) {
            cout << 1 << "\n";
            continue;
        }
        vector<bool> visited(n + 1, false);
        vector<int> dist(n + 1, 0);
        vector<int> bfsQueue;
        bfsQueue.push_back(s);
        visited[s] = true;
        dist[s] = 0;
        bool found = false;
        int head = 0;
        while (head < (int)bfsQueue.size() && !found) {
            int v = bfsQueue[head++];
            int d = dist[v];
            if (compRoot[v] == compRoot[t] && t <= v) {
                cout << d + 1 << "\n";
                found = true;
                break;
            }
            int root = compRoot[v];
            for (int w : compMembers[root]) {
                for (int u : adj[w]) {
                    if (u > v && !visited[u]) {
                        visited[u] = true;
                        dist[u] = d + 1;
                        bfsQueue.push_back(u);
                    }
                }
            }
        }
        if (!found) {
            cout << -1 << "\n";
        }
    }
    return 0;
}
