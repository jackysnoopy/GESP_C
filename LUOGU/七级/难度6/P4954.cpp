#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    // Tower of Hay: build tower with consecutive groups
    // Each layer's width <= previous layer's width
    // Maximize number of layers
    //
    // DP approach:
    // dp[i][j] = max layers using first i bales, last layer starts at j
    // dp[i][j] = max over k < j of dp[j-1][k] + 1, if sum(k..j-1) >= sum(j..i)
    //
    // Optimization: use prefix sums and greedy
    // For each position i, find the maximum number of layers ending at i
    //
    // Key insight: use DP where dp[i] = max layers for prefix i
    // Transition: dp[i] = max(dp[j] + 1) for j < i where
    //   sum of last layer (j+1..i) <= sum of second-to-last layer

    vector<int> ps(n + 1, 0);
    for (int i = 1; i <= n; i++) ps[i] = ps[i-1] + w[i];

    // dp[i] = max layers using bales 1..i
    // But we also need to track the width of the last layer
    //
    // Use: dp[i][j] = max layers using bales 1..i, with last layer width = j
    // Too expensive. Use different approach.
    //
    // For each possible number of layers h, check if it's achievable
    // Binary search on h, check in O(n) or O(n log n)
    //
    // Or: greedy from right to left
    // Last layer: take as few bales as possible from the right
    // Second-to-last: take at least as many
    // etc.

    // Greedy approach: from right to left
    // layer h (last): bales [n-h+1..n], width = sum
    // layer h-1: bales [n-h-h+1..n-h], width >= previous
    // etc.

    // Binary search on number of layers h
    // Check: can we partition 1..n into h layers where
    //   each layer's sum <= previous layer's sum (from bottom to top)

    auto check = [&](int h) -> bool {
        // Try to build h layers from right to left
        // Layer h (top): as few bales as possible from the right
        // Layer h-1: at least as wide
        // ...
        // Layer 1 (bottom): widest

        // From right to left:
        // Layer h: bales [r+1..n], width = ps[n] - ps[r]
        // Layer h-1: bales [l..r], width = ps[r] - ps[l-1] >= layer h width
        // etc.

        int remaining = h;
        int right = n;
        long long prev_width = 0;

        for (int layer = 0; layer < h; layer++) {
            // Current layer: bales [left..right]
            // Width = ps[right] - ps[left-1]
            // Must be >= prev_width (for layers above the current one)
            // Wait, layer 0 is the top (smallest), layer h-1 is the bottom (largest)
            // So from top to bottom, width is non-decreasing

            // Actually: from right to left, each layer must be >= previous
            // Top layer: some bales from the right
            // Each lower layer: at least as wide

            // Find the leftmost position such that width >= prev_width
            // and we leave enough bales for remaining layers

            int need = remaining; // bales needed for current and lower layers
            // Current layer needs at least 1 bale
            // Lower layers need at least 1 bale each

            // Binary search for left boundary
            int lo = max(1, right - (right - 1) + 1); // at least 1 bale
            int hi = right;
            int best = right;

            // Actually: we want the leftmost position left such that
            // ps[right] - ps[left-1] >= prev_width
            // and right - left + 1 >= 1 (at least 1 bale)
            // and we have enough bales for remaining layers below

            // Simple approach: from right, take bales until width >= prev_width
            long long width = 0;
            int left = right;
            while (left >= 1 && width < prev_width) {
                width += w[left];
                left--;
            }
            left++; // left is now the start of this layer

            if (width < prev_width) return false;
            if (left < 1 && layer < h - 1) return false;

            prev_width = width;
            right = left - 1;
            remaining--;
        }

        return right == 0; // all bales used
    };

    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
