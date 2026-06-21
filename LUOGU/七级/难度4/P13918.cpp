#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; i++) cin >> parent[i];

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++) children[parent[i]].push_back(i);

    vector<int> depth(n + 1, 0);
    vector<int> order;
    order.push_back(1);
    depth[1] = 0;

    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }

    vector<int> subtree_size(n + 1, 1);
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        if (parent[u] != 0) subtree_size[parent[u]] += subtree_size[u];
    }

    vector<int> candidates;
    for (int i = 2; i <= n; i++) {
        if (children[i].empty()) candidates.push_back(subtree_size[i]);
    }

    sort(candidates.begin(), candidates.end(), greater<int>());

    int ans = n;
    for (int i = 0; i < min(k, (int)candidates.size()); i++) {
        ans -= candidates[i];
    }

    cout << max(1, ans) << "\n";
    return 0;
}
