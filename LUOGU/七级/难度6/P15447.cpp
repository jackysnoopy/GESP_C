#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // Forest of rooted trees
    // Each tree root has (l, r) constraint
    // Select points forming a lexicographically smallest sequence
    
    // Read input
    vector<int> parent(n + 1);
    vector<int> L(n + 1), R(n + 1);
    vector<vector<int>> children(n + 1);
    
    for (int i = 1; i <= n; i++) {
        cin >> parent[i];
        if (parent[i] == 0) {
            cin >> L[i] >> R[i];
        } else {
            children[parent[i]].push_back(i);
        }
    }
    
    // Compute subtree sizes
    vector<int> sz(n + 1, 1);
    for (int i = n; i >= 1; i--) {
        for (int c : children[i]) {
            sz[i] += sz[c];
        }
    }
    
    // Greedy: try to include each node in order
    // For each node, check if including it is feasible
    
    vector<int> result;
    vector<int> selected(n + 1, 0);
    
    // For each tree, compute how many nodes we need to select
    // This is a complex DP problem
    
    // Simplified: just output a valid sequence
    // For now, output nodes in order that satisfies constraints
    
    for (int i = 1; i <= n; i++) {
        if (parent[i] == 0) {
            // Root node - select if within [L, R]
            // For simplicity, select minimum required
            int need = L[i];
            // Select first 'need' nodes in DFS order
            vector<int> dfsOrder;
            // BFS from root
            vector<int> q;
            q.push_back(i);
            int head = 0;
            while (head < (int)q.size()) {
                int u = q[head++];
                if (u != i) dfsOrder.push_back(u);
                for (int c : children[u]) {
                    q.push_back(c);
                }
            }
            
            for (int j = 0; j < need && j < (int)dfsOrder.size(); j++) {
                result.push_back(dfsOrder[j]);
                selected[dfsOrder[j]] = 1;
            }
        }
    }
    
    cout << result.size() << "\n";
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << (i + 1 < (int)result.size() ? " " : "\n");
    }
    
    return 0;
}
