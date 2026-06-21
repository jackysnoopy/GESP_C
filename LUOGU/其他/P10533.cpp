#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<double> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    // Compute distance from each city to capital (0,0)
    vector<double> d(n);
    for (int i = 0; i < n; i++) {
        d[i] = sqrt(x[i] * x[i] + y[i] * y[i]);
    }
    // Each city i (1-indexed, 0 is capital) chooses city j with d[j] <= d[i], j != i,
    // minimizing dis(i,j). If multiple, smallest index.
    // Build edges
    vector<int> parent(n + 1, -1); // parent[0] = 0 (capital)
    vector<vector<int>> adj(n + 1);
    // City 0 is capital (index 0 in 0-indexed)
    // Cities 1..n are the n cities (index 0..n-1 in input)
    // d[0] = 0 (capital)
    // For city i (input index i, which is city i+1 in 1-indexed):
    //   Find j with d[j] <= d[i], j != i, minimizing dis(i,j).
    //   dis(i,j) = sqrt((x[i]-x[j])^2 + (y[i]-y[j])^2).
    //   If no such j, parent is -1 (unreachable).
    //   Capital (d=0) is always available.
    
    for (int i = 0; i < n; i++) {
        double best_dist = 1e18;
        int best_j = -1;
        // Check capital first (index -1 in input, but d=0)
        // Actually, capital is at (0,0) with d=0. It's always <= d[i].
        // dis(i, capital) = d[i].
        best_dist = d[i];
        best_j = -1; // -1 represents capital
        for (int j = 0; j < n; j++) {
            if (j == i) continue;
            if (d[j] > d[i]) continue;
            double dist = sqrt((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
            if (dist < best_dist - 1e-9 || (fabs(dist - best_dist) < 1e-9 && j < best_j)) {
                best_dist = dist;
                best_j = j;
            }
        }
        parent[i] = best_j;
    }
    
    // Compute gamma values using BFS from capital
    vector<int> gamma(n + 1, 0); // gamma[capital] = 1
    gamma[n] = 1; // capital is index n (mapped from -1)
    // Actually, let me use a different indexing.
    // Capital = index n. Cities 0..n-1.
    vector<int> dist_from_cap(n + 1, -1);
    dist_from_cap[n] = 0;
    // Build adjacency from parent
    for (int i = 0; i < n; i++) {
        if (parent[i] == -1) {
            adj[n].push_back(i);
            adj[i].push_back(n);
        } else {
            adj[parent[i]].push_back(i);
            adj[i].push_back(parent[i]);
        }
    }
    // BFS
    vector<int> queue;
    queue.push_back(n);
    for (int qi = 0; qi < (int)queue.size(); qi++) {
        int u = queue[qi];
        for (int v : adj[u]) {
            if (dist_from_cap[v] == -1) {
                dist_from_cap[v] = dist_from_cap[u] + 1;
                queue.push_back(v);
            }
        }
    }
    // gamma[i] = dist_from_cap[i] + 1, or 0 if unreachable
    vector<int> gamma_vals;
    for (int i = 0; i < n; i++) {
        if (dist_from_cap[i] == -1) gamma_vals.push_back(0);
        else gamma_vals.push_back(dist_from_cap[i] + 1);
    }
    
    // Subset sum: can we partition gamma_vals into two equal-sum groups?
    long long total = 0;
    for (int g : gamma_vals) total += g;
    if (total % 2 != 0) { cout << "No\n"; return 0; }
    long long target = total / 2;
    
    // For n <= 500, subset sum with bitset
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (int g : gamma_vals) {
        for (long long j = target; j >= g; j--) {
            if (dp[j - g]) dp[j] = true;
        }
    }
    cout << (dp[target] ? "Yes" : "No") << "\n";
    return 0;
}
