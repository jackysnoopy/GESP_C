#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    long long total = 0;
    for (int i = 0; i < n; i++) { cin >> a[i]; total += a[i]; }
    
    // Each pile should have total/n or total/n + 1 cards
    long long base = total / n;
    int extra = total % n; // extra piles get base+1
    
    // Sort piles by position, assign targets
    // Actually, this is a transportation problem.
    // Source: pile i has a[i] cards. Target: pile i needs base (or base+1) cards.
    // Cost per card moved from i to j is |i-j|.
    // 
    // This is the Earth Mover's Distance / 1D optimal transport.
    // Greedy: process left to right, carry surplus/deficit.
    
    // Assign targets: first n-extra piles get base, last extra piles get base+1.
    // But which piles get base+1? To minimize cost, assign base+1 to piles closest
    // to where surplus is. Actually, the optimal assignment is to sort piles by position
    // and assign targets in order.
    
    // Actually, the optimal solution is: for each pile i, compute the prefix sum of
    // (a[i] - target[i]). The cost is sum of |prefix[i]|.
    // The target assignment that minimizes cost is to assign base+1 to the extra piles
    // that are "closest" to the surplus.
    
    // For 1D transport, the optimal target is: sort both sources and targets,
    // then match them in order.
    // Sources: a[0], a[1], ..., a[n-1] (at positions 0, 1, ..., n-1)
    // Targets: base (n-extra times) and base+1 (extra times) at positions 0, 1, ..., n-1
    // The optimal assignment of targets to positions is: put base+1 at positions that
    // minimize the total transport cost.
    
    // Actually, since all targets are at fixed positions (0..n-1), and sources are at
    // fixed positions, the optimal transport is determined by the prefix sum method.
    // We just need to decide which positions get base+1.
    
    // Key insight: the optimal assignment is to assign base+1 to positions 0..extra-1
    // (or any contiguous block) after sorting. But since positions are fixed, we need
    // to find the optimal assignment.
    
    // For 1D optimal transport with supplies and demands at fixed positions:
    // Sort supplies and demands by position, match in order.
    // Supplies: (a[i], i) sorted by a[i] (or by position?)
    // Actually, in 1D, the optimal transport matches supply i at position p_i
    // with demand j at position q_j, where both are sorted by position.
    // The cost is sum |p_i - q_j| * flow.
    
    // But here, supplies are at positions 0..n-1 with amounts a[i].
    // Demands are at positions 0..n-1 with amounts target[i].
    // The optimal transport cost is sum_{i=0}^{n-1} |sum_{j=0}^{i} (a[j] - target[j])|.
    
    // So we need to choose target[i] to minimize this sum.
    // target[i] is either base or base+1, with exactly extra piles getting base+1.
    
    // The prefix sum of (a[j] - target[j]) = prefix_a[j] - prefix_target[j].
    // We want to minimize sum |prefix_a[j] - prefix_target[j]|.
    // prefix_target[j] = base * (j+1) + (number of base+1 in positions 0..j).
    // Let x[j] = number of base+1 in positions 0..j. Then x[n-1] = extra.
    // prefix_target[j] = base * (j+1) + x[j].
    
    // We want to minimize sum |prefix_a[j] - base*(j+1) - x[j]|.
    // Let d[j] = prefix_a[j] - base*(j+1). We want to minimize sum |d[j] - x[j]|.
    // x[j] is non-decreasing, x[0] in {0,1}, x[j] - x[j-1] in {0,1}, x[n-1] = extra.
    
    // This is a DP problem. But n <= 1000, so O(n^2) is fine.
    
    vector<long long> pa(n + 1, 0);
    for (int i = 0; i < n; i++) pa[i + 1] = pa[i] + a[i];
    
    vector<long long> d(n);
    for (int i = 0; i < n; i++) d[i] = pa[i + 1] - base * (i + 1);
    
    // DP: dp[i][j] = min cost for first i piles with j base+1 assignments
    // dp[i][j] = min over dp[i-1][j] + |d[i-1] - j|, dp[i-1][j-1] + |d[i-1] - j|
    // (if j-1 >= 0)
    
    const long long INF = 1e18;
    vector<vector<long long>> dp(n + 1, vector<long long>(extra + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= min(i, extra); j++) {
            // Don't assign base+1 to position i-1
            if (dp[i-1][j] < INF) {
                dp[i][j] = min(dp[i][j], dp[i-1][j] + abs(d[i-1] - j));
            }
            // Assign base+1 to position i-1
            if (j > 0 && dp[i-1][j-1] < INF) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1] + abs(d[i-1] - j));
            }
        }
    }
    
    cout << dp[n][extra] << "\n";
    return 0;
}
