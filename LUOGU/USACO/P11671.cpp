#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long M;
        cin >> n >> M;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // For each x in [0, M-1], compute sum of min(a[i] % M - x % M adjusted) for all i
        // Actually: for each x, cost = sum_i min((a[i] - x) mod M, M - ((a[i] - x) mod M))
        // We want the minimum cost over all x.
        
        // Compute a[i] % M for all i
        vector<long long> r(n);
        for (int i = 0; i < n; i++) r[i] = a[i] % M;
        sort(r.begin(), r.end());
        
        // For a fixed x, the cost is:
        // For each r[i], the cost is min((r[i] - x + M) % M, M - (r[i] - x + M) % M)
        // = min((r[i] - x) mod M, M - (r[i] - x) mod M)
        // This is the circular distance from x to r[i] on a circle of circumference M.
        
        // To find the best x, we need to find the point on the circle that minimizes
        // the sum of circular distances to all r[i].
        
        // Key insight: on a circle, the optimal x is between two consecutive r[i] values.
        // We can try all possible x values that are midpoints of consecutive r[i] pairs,
        // or just the r[i] values themselves.
        
        // Actually, for the L1 circular median on a circle, the optimal point is at one of the r[i]
        // or at the antipodal point of one of the r[i].
        
        // Simpler approach: for each r[i] as candidate x:
        // But there might be a smarter O(n log n) approach.
        
        // For large n, use prefix sums approach.
        // For each candidate x, compute cost = sum of min(|r[i] - x|, M - |r[i] - x|)
        // where the distances are on a circle.
        
        // Binary search or sweep line approach:
        // The optimal x is one of the r[i] values (or their antipodal points).
        // Since M can be up to 10^9 and n up to 2*10^5, we try O(n) candidates.
        
        // For each r[i], consider x = r[i] as candidate.
        // Also consider x = (r[i] + M/2) % M.
        
        // Actually, the median on a circle: for even number of points, the median is the range [r[n/2-1], r[n/2]].
        // On a circle, we can "cut" the circle at any point and compute the linear median.
        
        // Best approach: 
        // 1. Duplicate the array: r[i] and r[i] + M
        // 2. For each possible "cut" (between consecutive r values), compute the linear cost
        // 3. Take the minimum
        
        // For a cut at position between r[j] and r[j+1]:
        // Points to the right stay, points to the left shift by +M
        // Then it's a linear problem: find median
        
        // This can be done in O(n log n) with sliding window.
        
        // Duplicate
        vector<long long> ext(2 * n);
        for (int i = 0; i < n; i++) {
            ext[i] = r[i];
            ext[i + n] = r[i] + M;
        }
        
        // For each window of n consecutive points in ext,
        // the cost is sum of distances to the median.
        // Use prefix sums.
        vector<long long> ps(2 * n + 1, 0);
        for (int i = 0; i < 2 * n; i++) ps[i + 1] = ps[i] + ext[i];
        
        long long best = 1e18;
        for (int i = 0; i < n; i++) {
            // Window: ext[i], ext[i+1], ..., ext[i+n-1]
            // Median is ext[i + n/2]
            int mid = i + n / 2;
            long long med = ext[mid];
            // Cost = sum of |ext[j] - med| for j in [i, i+n-1]
            // = (med * left_count - sum_left) + (sum_right - med * right_count)
            long long leftSum = ps[mid] - ps[i];
            long long rightSum = ps[i + n] - ps[mid + 1];
            long long leftCount = mid - i;
            long long rightCount = i + n - 1 - mid;
            long long cost = med * leftCount - leftSum + rightSum - med * rightCount;
            if (cost < best) best = cost;
        }
        
        cout << best << "\n";
    }
    return 0;
}
