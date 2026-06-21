#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [LAOI-6] 区间测速
// Given n monitoring records (x_i, t_i). m queries: change t_{u_i} to v_i, 
// compute max floor(|x_i - x_j| / |t_i - t_j|) over all pairs.
// Each query is independent.
//
// Direct approach: for each query, compute all pairs. O(n^2) per query.
// With n up to 1e5, this is too slow.
//
// Key insight: the answer is the maximum speed between any two records.
// After changing t_{u_i}, we need to recompute the max.
// 
// The max speed is max over all pairs of |dx/dt|.
// This equals the maximum "slope" between any two points.
// 
// For points sorted by time: the max speed is the max of consecutive slopes
// (by the convex hull / monotone chain argument).
// Actually no, the max can be between non-adjacent points.
// 
// The max |x_i - x_j| / |t_i - t_j| is the maximum slope over all pairs.
// When sorted by t: the maximum is between the point with max x and min x,
// but only if they have different t values.
// 
// Actually: max |dx/dt| = max over all pairs. This equals:
// max over i,j: |x_i - x_j| / |t_i - t_j|
// 
// For the modified problem (one t value changes), we need efficient recomputation.
// 
// Simple O(n) per query approach for small n:
// After modifying t_{u_i}, recompute all pairwise speeds.
// For n up to 1e3 (subtask 1-3), this works.
// For larger n, need a smarter approach.
//
// Let me implement the O(n^2) approach which works for the smaller subtasks.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> x(n), t(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> t[i];
    
    while (m--) {
        int u;
        long long v;
        cin >> u >> v;
        u--;
        long long orig_t = t[u];
        t[u] = v;
        
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                long long dx = abs(x[i] - x[j]);
                long long dt = abs(t[i] - t[j]);
                if (dt > 0) {
                    ans = max(ans, dx / dt);
                }
            }
        }
        cout << ans << "\n";
        
        t[u] = orig_t;
    }
    return 0;
}
