#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> h(n);
    long long total = 0;
    for (int i = 0; i < n; i++) { cin >> h[i]; total += h[i]; }
    long long avg = total / n;
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // DFS from root 0. For each subtree, compute surplus/deficit.
    // The number of commands = number of edges with non-zero flow.
    vector<long long> surplus(n);
    for (int i = 0; i < n; i++) surplus[i] = h[i] - avg;
    
    vector<pair<int,int>> commands;
    
    // Post-order DFS
    vector<int> parent(n, -1);
    vector<int> order;
    vector<int> stack;
    stack.push_back(0);
    parent[0] = -2;
    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();
        order.push_back(u);
        for (int v : adj[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            stack.push_back(v);
        }
    }
    
    // Process in reverse order (post-order)
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (parent[u] >= 0) {
            surplus[parent[u]] += surplus[u];
            if (surplus[u] != 0) {
                if (surplus[u] > 0) {
                    commands.push_back(make_pair(u, parent[u]));
                } else {
                    commands.push_back(make_pair(parent[u], u));
                }
            }
        }
    }
    
    // For edges with non-zero surplus, we need to move |surplus| units.
    // But we might need multiple commands per edge if surplus > h[source].
    // Actually, the problem says we can move any positive amount up to h[source].
    // So one command per edge is sufficient (move the exact amount).
    
    // But wait, the surplus might be larger than h[u] at the time of the command.
    // We need to ensure that when we issue the command, the source has enough hay.
    // The correct approach: process in topological order (leaves first).
    // Each edge: move surplus[u] from u to parent[u] (or vice versa).
    // Since we process leaves first, by the time we process an edge,
    // the child has accumulated all its subtree's surplus.
    
    // But the source might not have enough hay if surplus > h[u].
    // Actually, surplus[u] = total hay in subtree - avg * subtree_size.
    // If surplus[u] > 0, the subtree has excess. The child u has accumulated
    // all the excess from its subtree. So h[u] (after processing children)
    // should be >= surplus[u].
    
    // Hmm, actually h[u] changes as we process commands. Let me think...
    // After processing all children of u, u has h[u] + sum of children's contributions.
    // The surplus[u] is exactly this total excess. So u has surplus[u] extra hay.
    // We move surplus[u] to parent. This is valid as long as surplus[u] > 0.
    
    cout << commands.size() << "\n";
    for (auto& cmd : commands) {
        cout << cmd.first + 1 << " " << cmd.second + 1 << " " << abs(surplus[cmd.first > cmd.second ? cmd.first : cmd.second]) << "\n";
    }
    
    return 0;
}
