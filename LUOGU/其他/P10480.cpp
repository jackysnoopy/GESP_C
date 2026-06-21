#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

const int MAXN = 30000;
typedef bitset<MAXN> BS;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        ++indeg[y];
    }

    vector<int> order;
    order.reserve(n);
    vector<int> q;
    for (int i = 1; i <= n; ++i) if (indeg[i] == 0) q.push_back(i);
    for (int front = 0; front < (int)q.size(); ++front) {
        int u = q[front];
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) q.push_back(v);
        }
    }

    vector<BS> reach(n + 1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        reach[u].set(u - 1);
        for (int v : adj[u]) reach[u] |= reach[v];
    }

    for (int i = 1; i <= n; ++i) cout << (int)reach[i].count() << '\n';
    return 0;
}
