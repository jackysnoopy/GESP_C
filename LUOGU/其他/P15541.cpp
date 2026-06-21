#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long A, B, K;
    int T;
    cin >> A >> B >> K >> T;
    long long d = abs(A - B);
    if (d == 0) { cout << 0 << "\n"; return 0; }
    // Fewest hops: use as many giant hops as possible
    // d = q*K + r, 0 <= r < K
    // If r == 0: q giant hops
    // If r > 0: q giant hops + 1 baby hop = q+1 total
    // But we can also do (q+1) giant hops + baby hop back: (q+1)+1 = q+2
    // For T=1: answer is ceil(d/K) or d/K if d%K==0? No.
    // Actually: d = q*K + r. 
    // Strategy 1: q giant + r baby = q + r hops (if r > 0)
    // Strategy 2: (q+1) giant + (K-r) baby back = q + 1 + K - r hops
    // Strategy 3: (q-1) giant + (K+r) baby = q - 1 + K + r hops (worse)
    // Min is min(q + r, q + 1 + K - r) for r > 0, or q for r == 0.
    long long q = d / K;
    long long r = d % K;
    long long ans1;
    if (r == 0) {
        ans1 = q;
    } else {
        ans1 = min(q + r, q + 1 + K - r);
    }
    if (T == 1) {
        cout << ans1 << "\n";
    } else {
        // Second fewest: find the next best strategy
        // Candidates: 
        // 1. q + r (if r > 0)
        // 2. q + 1 + K - r (if r > 0)
        // 3. (q+1) + r (one more giant hop, baby hops for remainder) = q + 1 + r
        // 4. (q-1) + K + r = q + K + r - 1 (if q >= 1)
        // 5. (q+2) + K - r = q + 2 + K - r (if r > 0)
        // 6. q + K + (K-r) - wait...
        // Actually the strategies are:
        // Use g giant hops and b baby hops where g*K + b >= d and we end at B.
        // More precisely: g giant hops can get us to position d mod K away (or K - d mod K),
        // then b baby hops close the gap.
        // 
        // With g giant hops: position mod K = (g * K) mod K = 0? No.
        // If all hops are forward: position = g*K. Need |g*K - d| baby hops.
        // If some hops backward: could reach d - g*K or g*K - d.
        // 
        // Actually: g giant hops in any direction, net displacement = g*K (all forward) 
        // or (g-2)*K, (g-4)*K, ... (g mod 2) * K.
        // So net giant displacement is g*K - 2*j*K for some j, i.e., |g*K - 2j*K|.
        // Actually net = (g - 2j)*K where 0 <= j <= g.
        // So net giant displacement can be g*K, (g-2)*K, ..., -g*K (if g even) or K (if g odd).
        // Basically net giant = (g mod 2) * K, (g-2)*K, ..., up to g*K.
        // The set is {g*K, (g-2)*K, ..., (g mod 2)*K, -(g mod 2)*K, ..., -g*K}.
        // So net = m*K where |m| <= g and m ≡ g (mod 2).
        // Remaining: d - m*K baby hops = |d - m*K|.
        // Total: g + |d - m*K|.
        // We want the second smallest total.
        // 
        // For g = ceil(d/K): m*K closest to d. m = floor(d/K) or ceil(d/K).
        // For g = ceil(d/K) + 1: same idea.
        // 
        // Let me enumerate candidates for the second smallest.
        long long best1 = ans1;
        long long best2 = (long long)1e18;
        for (long long g = 0; g <= q + 3 && g <= 20; g++) {
            // m can be g, g-2, g-4, ...
            for (long long m = g; m >= -g; m -= 2) {
                long long baby = abs(d - m * K);
                long long total = g + baby;
                if (total > best1 && total < best2) best2 = total;
            }
        }
        // Also try larger g values
        for (long long g = max(0LL, q - 3); g <= q + 5; g++) {
            for (long long m = g; m >= -g; m -= 2) {
                long long baby = abs(d - m * K);
                long long total = g + baby;
                if (total > best1 && total < best2) best2 = total;
            }
        }
        cout << best2 << "\n";
    }
    return 0;
}
