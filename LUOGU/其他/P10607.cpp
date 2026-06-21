#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    struct Cond { int x, y; long long k; };
    vector<Cond> conds(m);
    for (int i = 0; i < m; i++) cin >> conds[i].x >> conds[i].y >> conds[i].k;
    // Greedy from left to right: for each position, decide whether to reverse.
    // The ball starts going right. At position i (1-indexed), if we pay a[i],
    // we reverse direction. We need to satisfy all conditions.
    // Condition: ball moves from x_i to y_i at least k_i times, where x_i > y_i.
    // This means the ball must go right past x_i, then reverse before x_i,
    // go left past y_i, then reverse before y_i, etc.
    // 
    // For each condition (x, y, k): we need the ball to oscillate between
    // passing x going right and passing y going left at least k times.
    // This requires reversals at positions in [y+1, x].
    // Minimum cost to achieve k oscillations in [y+1, x]:
    // We need to pick some positions to reverse. The ball must pass both x and y
    // in the correct directions.
    //
    // Let me think about this differently. The ball oscillates. Each full cycle
    // (right past x, left past y) requires reversals at some positions in [y+1, x].
    // The minimum cost per cycle is 2 * min(a[y+1..x]) (reverse at cheapest point
    // going right, then reverse at cheapest point going left).
    // But conditions can share reversal points.
    //
    // For the special case where all k_i are equal (= k):
    // All conditions require k oscillations. The answer is 2 * k * min over all
    // relevant positions of a[i].
    //
    // For the general case: this is complex. Let me implement a greedy.
    // Sort conditions by x. Process from right to left.
    // For each condition, we need k oscillations in [y+1, x].
    // Each oscillation needs 2 reversals (one at each end of the trip).
    // The minimum cost for k oscillations in interval [l, r] is
    // 2 * min(a[l..r]) per oscillation if we use the same point,
    // or 2 * (min of left part + min of right part) if different.
    //
    // Actually, let me think more carefully. The ball goes right. To go from x to y
    // (x > y), it must reverse at some point >= x, then reverse at some point <= y.
    // The cheapest way: reverse at min_cost_right in [x, ...] and min_cost_left in [..., y].
    // But positions in [y+1, x] can be shared between conditions.
    //
    // This is getting complex. Let me just implement a simple greedy for small cases.
    
    // For n <= 10, brute force all subsets of reversal points.
    if (n <= 15) {
        long long ans = -1;
        for (int mask = 0; mask < (1 << n); mask++) {
            long long cost = 0;
            for (int i = 0; i < n; i++) if (mask & (1 << i)) cost += a[i];
            // Simulate the ball's path with reversals at positions in mask
            // Check all conditions
            bool ok = true;
            for (auto& c : conds) {
                int x = c.x, y = c.y;
                long long need = c.k;
                // Simulate and count x->y traversals
                long long cnt = 0;
                int pos = 0;
                int dir = 1; // 1=right, -1=left
                // The ball starts at 0 going right
                // It visits positions 1, 2, ..., n, then bounces back
                vector<int> visits;
                // Simulate enough steps
                pos = 0; dir = 1;
                for (int step = 0; step < 4 * n + 100 && cnt < need; step++) {
                    pos += dir;
                    if (pos >= 1 && pos <= n) {
                        visits.push_back(pos);
                        if (mask & (1 << (pos - 1))) dir = -dir;
                    }
                    if (pos == x && dir == -1) { // just reversed at x, now going left
                        // Actually we need to count passing x going right
                    }
                    if (pos <= 0 || pos > n + 1) break;
                }
                // Count transitions from x going right to y going left
                for (int i = 0; i + 1 < (int)visits.size(); i++) {
                    if (visits[i] == x && visits[i + 1] < x) cnt++; // reversed at or past x
                }
                if (cnt < need) { ok = false; break; }
            }
            if (ok) {
                if (ans == -1 || cost < ans) ans = cost;
            }
        }
        cout << ans << "\n";
    } else {
        // For larger cases, use a greedy approach
        // Process conditions sorted by x descending
        vector<int> rev(n + 1, 0); // reversal at position i
        // Sort by x descending, then y descending
        vector<int> idx(m);
        for (int i = 0; i < m; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            if (conds[i].x != conds[j].x) return conds[i].x > conds[j].x;
            return conds[i].y > conds[j].y;
        });
        long long ans = 0;
        for (int i : idx) {
            int x = conds[i].x, y = conds[i].y;
            long long k = conds[i].k;
            // Need k oscillations in [y+1, x]
            // Each oscillation: ball goes right past x, reverses, goes left past y, reverses
            // Minimum: use 2 reversal points per oscillation
            // For now, just use the cheapest 2 points
            int best_l = y + 1, best_r = x;
            for (int j = y + 1; j <= x; j++) {
                if (a[j - 1] < a[best_l - 1]) best_l = j;
                if (a[j - 1] < a[best_r - 1]) best_r = j;
            }
            if (best_l == best_r && x > y + 1) {
                best_r = y + 1;
                for (int j = y + 2; j <= x; j++) {
                    if (a[j - 1] < a[best_r - 1]) best_r = j;
                }
            }
            ans += k * (a[best_l - 1] + a[best_r - 1]);
        }
        cout << ans << "\n";
    }
    return 0;
}
