#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    vector<bool> is_child(n + 1, false);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        children[u].push_back(v);
        parent[v] = u;
        is_child[v] = true;
    }

    int root = 1;
    for (int i = 1; i <= n; i++) {
        if (!is_child[i]) {
            root = i;
            break;
        }
    }

    vector<int> order;
    {
        vector<int> q;
        q.push_back(root);
        int head = 0;
        while (head < (int)q.size()) {
            int u = q[head++];
            order.push_back(u);
            for (int v : children[u]) q.push_back(v);
        }
    }

    vector<long long> mx(n + 1);
    vector<int> bc(n + 1, -1);
    vector<priority_queue<pair<long long, int>>> heaps(n + 1);

    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        mx[u] = w[u];
        bc[u] = -1;
        for (int v : children[u]) {
            heaps[u].push({mx[v], v});
        }
        if (!heaps[u].empty()) {
            mx[u] = w[u] + heaps[u].top().first;
            bc[u] = heaps[u].top().second;
        }
    }

    long long ans = 0;
    for (int iter = 0; iter < k; iter++) {
        if (mx[root] <= 0) break;
        ans += mx[root];

        vector<int> path;
        int u = root;
        while (u != -1) {
            path.push_back(u);
            w[u] = 0;
            u = bc[u];
        }

        for (int i = (int)path.size() - 1; i >= 0; i--) {
            int node = path[i];
            while (!heaps[node].empty() && mx[heaps[node].top().second] != heaps[node].top().first) {
                heaps[node].pop();
            }
            if (heaps[node].empty()) {
                mx[node] = 0;
                bc[node] = -1;
            } else {
                mx[node] = heaps[node].top().first;
                bc[node] = heaps[node].top().second;
            }
            if (parent[node] != 0) {
                heaps[parent[node]].push({mx[node], node});
            }
        }
    }

    cout << ans << endl;
    return 0;
}
