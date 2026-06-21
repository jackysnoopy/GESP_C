#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> depth(n + 1, 0);
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    parent[1] = 0;
    depth[1] = 0;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }
    }

    int max_depth = *max_element(depth.begin(), depth.end());
    int p = 0;
    long long total = 1;
    long long cap = 1;
    while (total < n) {
        p++;
        cap *= k;
        total += cap;
    }

    int q = 0;
    for (int i = n - 1; i >= 1; i--) {
        int u = order[i];
        if (adj[u].size() < k) {
            q++;
        }
    }

    cout << p << " " << q << "\n";
    return 0;
}
