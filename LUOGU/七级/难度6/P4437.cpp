#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
int n;
int a[MAXN], w[MAXN];
vector<int> adj[MAXN];
int deg[MAXN];
int order[MAXN];
int bit[MAXN];

void add(int i, int v) {
    for (; i <= n; i += i & (-i)) bit[i] += v;
}

int query(int i) {
    int s = 0;
    for (; i > 0; i -= i & (-i)) s += bit[i];
    return s;
}

int kth(int k) {
    int pos = 0;
    for (int pw = 1 << 19; pw; pw >>= 1)
        if (pos + pw <= n && bit[pos + pw] < k)
            pos += pw, k -= bit[pos];
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    // Build dependency graph: node i depends on a[i] (if a[i] > 0)
    // i must appear after position a[i] in the permutation
    for (int i = 1; i <= n; i++) {
        if (a[i] > 0) {
            adj[a[i]].push_back(i);
            deg[i]++;
        }
    }
    // Topological sort
    vector<int> q;
    for (int i = 1; i <= n; i++)
        if (deg[i] == 0) q.push_back(i);
    int head = 0;
    int cnt = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        order[++cnt] = u;
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) q.push_back(v);
        }
    }
    if (cnt < n) {
        cout << -1 << "\n";
        return 0;
    }
    // Now we have a topological order
    // We need to assign positions 1..n to maximize Σ i * w[p_i]
    // The constraint: if a[p_j] = p_k with k < j, then it's OK
    // Actually the constraint is: for the permutation p, 
    // if p_k = a_{p_j} then k < j
    // In topological order, if a[i] = j, then j comes before i
    // So in the permutation, position of j < position of i
    // We want to assign the largest weights to the largest positions
    // Subject to: the topological order constraint

    // Greedy: process in topological order, assign each node to the
    // latest available position (to maximize weight * position)
    // But we need to be careful: nodes with dependencies must come after
    // their dependencies.

    // Use BIT to track available positions
    for (int i = 1; i <= n; i++) add(i, 1);
    // For each node in topological order, assign it to position = 
    // the (number of nodes that must come after it + 1)-th available position
    // Actually: we want to assign nodes to positions greedily.
    // Process nodes in topological order. For each node,
    // it needs to be placed after all its predecessors.
    // We want to maximize Σ pos[i] * w[i].
    // So we should place high-weight nodes at high positions.

    // Better approach: sort nodes by weight (descending), then for each node,
    // assign it to the rightmost available position that satisfies the constraint.
    // But the constraint is: node i must be after node a[i] (if a[i] > 0).

    // Use the "latest available" approach:
    // For each node in order of decreasing weight:
    //   Find the latest position where it can be placed
    //   (must be after all nodes that depend on it being before... no, it's the other way)
    //   Node i must be after node a[i]. So position[i] > position[a[i]].

    // For nodes with a[i] = 0 (no constraint), they can be placed anywhere.
    // For nodes with a[i] > 0, they must be after a[i].

    // Process: assign positions from n down to 1
    // For each position, pick the available node with highest weight
    // that can be placed at this position (i.e., all nodes that must come after it
    // are already placed, and all nodes that must come before it are not yet placed).

    // This is complex. Let me use a simpler approach:
    // Process nodes in topological order. For node i,
    // it must be placed after all nodes in its "ancestor" chain.
    // The number of ancestors of i (including a[i], a[a[i]], etc.) determines
    // the earliest position it can be placed.

    // Actually, in the topological order, node i appears after all its ancestors.
    // So if node i is at position k in the topological order, it must be placed
    // at position >= k in the permutation.

    // To maximize Σ pos * w, we want high-weight nodes at high positions.
    // So: sort by weight descending. For each node (in weight order),
    // assign it to the latest available position >= its topological rank.

    // Compute topological rank for each node
    vector<int> topo_rank(n + 1);
    for (int i = 1; i <= n; i++) topo_rank[order[i]] = i;

    // Sort nodes by weight descending
    vector<int> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = i + 1;
    sort(nodes.begin(), nodes.end(), [&](int x, int y) {
        return w[x] > w[y];
    });

    // BIT to track available positions
    for (int i = 1; i <= n; i++) bit[i] = 0;
    for (int i = 1; i <= n; i++) add(i, 1);

    long long ans = 0;
    for (int i : nodes) {
        // Find the latest available position >= topo_rank[i]
        // We want position p such that p >= topo_rank[i] and p is available
        // Use BIT to find the last available position in [topo_rank[i], n]
        int avail = query(n) - query(topo_rank[i] - 1);
        if (avail <= 0) continue; // shouldn't happen
        // Find the avail-th available position from topo_rank[i]
        int target = query(topo_rank[i] - 1) + avail;
        int pos = kth(target);
        add(pos, -1);
        ans += (long long)pos * w[i];
    }
    cout << ans << "\n";
    return 0;
}
