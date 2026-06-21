#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int totalBlack = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] == 1) totalBlack++;
    }
    if (totalBlack <= 1) {
        cout << 0 << "\n";
        return 0;
    }
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // DFS from root=1, compute hasBlack[u] = number of black nodes in subtree
    vector<int> hasBlack(n + 1, 0);
    vector<int> parent(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    parent[1] = 0;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : g[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                order.push_back(v);
            }
        }
    }
    // Process in reverse order (bottom-up)
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        hasBlack[u] = a[u];
        for (int v : g[u]) {
            if (v != parent[u]) hasBlack[u] += hasBlack[v];
        }
    }
    // A node is in the Steiner tree iff:
    // - It's black, OR
    // - It has at least one child v with 0 < hasBlack[v] < totalBlack (edge in Steiner tree on child side),
    //   OR its parent edge is in the Steiner tree (hasBlack[u] > 0 && hasBlack[u] < totalBlack)
    // Simpler: node is in Steiner tree iff it's on some path between two black nodes
    // Edge (u, parent) is in Steiner tree iff 0 < hasBlack[u] < totalBlack
    // Node is in Steiner tree iff it's black or has at least one incident edge in Steiner tree
    int ans = 0;
    for (int u = 1; u <= n; u++) {
        if (a[u] == 1) continue; // already black
        // Check if u is in Steiner tree: any incident edge is in Steiner tree?
        bool inSteiner = false;
        if (hasBlack[u] > 0 && hasBlack[u] < totalBlack) inSteiner = true; // edge to parent
        if (!inSteiner) {
            for (int v : g[u]) {
                if (v == parent[u]) continue;
                if (hasBlack[v] > 0 && hasBlack[v] < totalBlack) { inSteiner = true; break; }
            }
        }
        if (inSteiner) ans++;
    }
    cout << ans << "\n";
    return 0;
}
