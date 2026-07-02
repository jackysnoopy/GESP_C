#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    double k1, k2;
    int m, n;
    cin >> k1 >> k2 >> m >> n;
    double total = 0;
    // Divide [0, 100] into m segments for north, n segments for south
    // North partition must be refinement of south partition
    // dp[i][j] = min cost using i north partitions and j south partitions
    // Brute force for small m, n (both ≤ 100)
    const int MAXN = 105;
    double dp[MAXN][MAXN];
    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= n; j++)
            dp[i][j] = 1e18;
    dp[0][0] = 0;
    // We enumerate the split points
    // Each segment [a, b] in north contributes k1*(b-a)^2/2 area
    // Each segment [a, b] in south contributes k2*(b-a)^2/2 area
    // But north segments must align with south segment boundaries
    // Simpler: enumerate all possible ways to split [1,99]
    // For each possible set of south splits, find optimal north splits
    // Since m, n ≤ 100, try DP over positions
    // dp[i][j] = min cost to cover positions [0..i] with j splits done
    // Actually: positions are 1..99, split points are integers in [1,99]
    // Let's use: dpNorth[i] = min cost to split [1..i] into some segments
    // dpSouth[i] = similarly
    // Constraint: every north split point is also a south split point
    // This means north segments are unions of consecutive south segments
    // So we first choose n-1 split points for south, then within each
    // south segment, we can add north split points

    // Alternative simpler approach:
    // Enumerate south split points (choose n-1 from 1..99)
    // Then for each south segment of length L, we can put some north segments
    // Cost of a segment of length L split into p parts: k * sum((L/p)^2) = k*L^2/p
    // Actually for even split: each part is L/p, total area = k * p * (L/p)^2 = k*L^2/p

    // Better approach: DP
    // f[i][j] = min cost to handle interval [0, i] with j south segments
    // using optimal north segments within the constraint
    // For each south segment [a, i], cost = k2*(i-a)^2 + min over splitting into
    // north segments (at least 1 per south segment, total m)

    // Let's precompute: for interval of length L, split into p north segments
    // min cost = k1 * L^2 / p (by AM-QM, equal splits are optimal)
    const int POS = 100;
    // dp_south[j][pos] = min cost covering [1..pos] with j south segments
    // where each south segment also has optimal north splits
    // We need to track how many north segments used

    // dp[j][k][pos] might be too big. Let's try:
    // For a south segment of length L with p north sub-segments:
    // north cost = k1 * L^2 / p
    // south cost = k2 * L^2
    // Total for this segment = L^2 * (k2 + k1/p)
    // We want to distribute m north segments among n south segments
    // to minimize total cost

    // Enumerate: for each south segment of length L_i,
    // assign p_i north segments (p_i >= 1, sum p_i = m)
    // cost_i = L_i^2 * (k2 + k1/p_i)

    // Precompute for each possible length L and number of north parts p:
    // cost[L][p] = L*L * (k2 + k1/p)

    // Then DP: split [1..99] into n south segments
    // For each split, assign north parts optimally
    // This is complex. Let's use simpler DP.

    // DP over positions with state (south_segments_used, north_segments_used)
    // dp[s][p] = min cost covering up to current position
    // Actually let's enumerate split positions one by one.

    // Simplest correct approach for small n,m ≤ 100:
    // dp[i][j] = min cost covering interval [1, i] with j south segments
    // Transition: dp[i][j] = min over k < i of dp[k][j-1] + cost of south segment [k+1, i]
    // where cost = (i-k)^2 * k2 + (i-k)^2 * k1 / (north parts for this segment)
    // But we need to track north parts globally...

    // Use dp[i][j][p] = min cost covering [1,i] with j south, p north parts
    // i up to 99, j up to 100, p up to 100 => 99*100*100 = ~10^6, feasible

    double dp3[MAXN][MAXN][MAXN];
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            for (int p = 0; p < MAXN; p++)
                dp3[i][j][p] = 1e18;
    dp3[0][0][0] = 0;
    for (int i = 1; i <= 99; i++) {
        for (int j = 1; j <= min(i, n); j++) {
            for (int p = j; p <= min(i, m); p++) {
                for (int k = j - 1; k < i; k++) {
                    int prev_p_max = p - 1;
                    if (k < j - 1) continue;
                    // south segment [k+1, i], length = i - k
                    int len = i - k;
                    // assign some north parts to this segment
                    // we need at least 1 north part per south segment
                    // try all possible north parts for this segment
                    for (int np = 1; np <= p - (j - 1); np++) {
                        if (k == 0 && j == 1) {
                            // first segment
                            double cost = (double)len * len * (k2 + k1 / np);
                            dp3[i][j][p] = min(dp3[i][j][p], cost);
                        } else if (k >= j - 1) {
                            double prev = dp3[k][j - 1][p - np];
                            if (prev < 1e17) {
                                double cost = (double)len * len * (k2 + k1 / np);
                                dp3[i][j][p] = min(dp3[i][j][p], prev + cost);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%.1f\n", dp3[99][n][m]);
    return 0;
}
