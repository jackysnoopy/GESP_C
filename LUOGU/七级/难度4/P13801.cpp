#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> depth(n, 0);
    vector<int> parent(n, -1);
    vector<int> order;
    order.push_back(0);
    parent[0] = -1;

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
    int diameter = 0;

    for (int i = 0; i < n; i++) {
        if (depth[i] == max_depth) {
            int cur = i;
            while (parent[cur] != -1) {
                cur = parent[cur];
                diameter++;
            }
            break;
        }
    }

    int ans = min(p, diameter + 1);
    cout << ans << "\n";

    return 0;
}
