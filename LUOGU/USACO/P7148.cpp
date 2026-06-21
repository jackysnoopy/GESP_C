#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> depth(N + 1, 0);
    vector<int> parent(N + 1, 0);
    vector<int> order;
    vector<bool> visited(N + 1, false);
    order.push_back(1);
    visited[1] = true;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }
    }
    int ans = 0;
    vector<int> infected(N + 1, 0);
    infected[1] = 1;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        if (infected[u] == 0) continue;
        int children = 0;
        for (int v : adj[u]) {
            if (v != parent[u]) children++;
        }
        if (children == 0) continue;
        while (infected[u] < children + 1) {
            infected[u] *= 2;
            ans++;
        }
        for (int v : adj[u]) {
            if (v != parent[u]) infected[v]++;
        }
    }
    cout << ans << "\n";
    return 0;
}
