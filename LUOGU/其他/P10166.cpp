#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Find minimum cost to create a cycle of length >= 2.
    // Cost of adding edge i->j is a[i] + a[j].
    // If a cycle already exists, cost is 0.
    // Otherwise, find the minimum cost 2-cycle: min over all i!=j of a[i]+a[j].
    // = two smallest values.
    // But we also need to check if a longer cycle exists for less cost.
    // A k-cycle has cost = sum of a[i] for each edge. Each edge i->j costs a[i]+a[j].
    // But each node appears in exactly one edge as source and one as target.
    // So total cost = sum of a[i] for all i in the cycle (each counted once as source).
    // Wait, each edge i->j costs a[i]+a[j]. For a cycle i1->i2->...->ik->i1:
    // Cost = (a[i1]+a[i2]) + (a[i2]+a[i3]) + ... + (a[ik]+a[i1])
    // = 2*(a[i1]+a[i2]+...+a[ik]).
    // For a 2-cycle i->j->i: cost = 2*(a[i]+a[j]).
    // For a k-cycle: cost = 2*sum of a[i] for i in cycle.
    // To minimize: use the cycle with the smallest sum of a[i].
    // The minimum is 2*(a[smallest] + a[second_smallest]) for a 2-cycle.
    // But we need the edges to exist or we add them.
    //
    // Actually, we can add ANY edge. So we can always create a 2-cycle.
    // The minimum cost is 2*(two smallest a[i] values).
    // But wait, we need k >= 2, so a 2-cycle is valid.
    // And the cost of adding edge i->j is a[i]+a[j].
    // For a 2-cycle i->j and j->i: total cost = (a[i]+a[j]) + (a[j]+a[i]) = 2*(a[i]+a[j]).
    // Minimum: 2*(smallest + second_smallest).
    //
    // But we might also find a cycle in the existing edges for free.
    // So first check if a cycle exists. If yes, answer is 0.
    // If not, answer is 2*(two smallest values).
    //
    // Check for cycle: DFS or topological sort on the directed graph.
    
    // Check for existing cycle
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; u--; v--;
        adj[u].push_back(v);
        indeg[v]++;
    }
    // Topological sort
    vector<int> q;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push_back(i);
    int cnt = 0;
    for (int i = 0; i < (int)q.size(); i++) {
        cnt++;
        for (int v : adj[q[i]]) {
            indeg[v]--;
            if (indeg[v] == 0) q.push_back(v);
        }
    }
    if (cnt < n) { cout << 0 << "\n"; return 0; }
    
    // No cycle. Find two smallest a[i].
    long long m1 = 1e18, m2 = 1e18;
    for (int i = 0; i < n; i++) {
        if (a[i] < m1) { m2 = m1; m1 = a[i]; }
        else if (a[i] < m2) m2 = a[i];
    }
    cout << 2 * (m1 + m2) << "\n";
    return 0;
}
