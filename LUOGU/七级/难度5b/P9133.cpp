#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    vector<int> parent(n + 1, 0);
    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        parent[i] = p;
        children[p].push_back(i);
    }

    vector<int> sz(n + 1, 1), dep(n + 1, 0);
    for (int i = 2; i <= n; i++) dep[i] = dep[parent[i]] + 1;

    // Post-order to compute subtree sizes
    vector<int> order;
    vector<int> stk = {1};
    while (!stk.empty()) {
        int u = stk.back(); stk.pop_back();
        order.push_back(u);
        for (int v : children[u]) stk.push_back(v);
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        for (int v : children[u]) sz[u] += sz[v];
    }

    // val(x) = (subtree_size(x) - 1) - depth(x)
    // diff(x) = val(x) - w(x)
    // W_profit = sum of diff(x) for W's nodes (after sorting by diff desc, W picks odd positions)
    vector<long long> diff(n);
    for (int i = 1; i <= n; i++) {
        long long val = (long long)(sz[i] - 1) - dep[i];
        diff[i - 1] = val - w[i];
    }

    sort(diff.begin(), diff.end(), greater<long long>());

    long long ans = 0;
    for (int i = 0; i < n; i += 2) ans += diff[i];

    cout << ans << "\n";
    return 0;
}
