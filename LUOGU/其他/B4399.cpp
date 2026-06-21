#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<long long,long long>> intervals(n);
    for (int i = 0; i < n; i++) cin >> intervals[i].first >> intervals[i].second;
    sort(intervals.begin(), intervals.end(), [](const pair<long long,long long>& a, const pair<long long,long long>& b) {
        return a.second < b.second;
    });
    // Process from right to left. Place point at left endpoint of uncovered interval.
    // Mark all intervals with l <= pt <= r as covered.
    // Optimization: since intervals are sorted by right endpoint, once we find an interval
    // not covered, we place a point and skip all intervals with r >= pt.
    // Wait, that's not right. We need to check l <= pt <= r.
    // Since intervals are sorted by r ascending, processing from right:
    // For interval i with r_i, we place at l_i. All intervals j with j < i have r_j <= r_i.
    // Interval j is covered if l_j <= l_i <= r_j. Since r_j <= r_i and l_i <= r_i,
    // we need l_j <= l_i and l_i <= r_j. The second condition: l_i <= r_j.
    // Since r_j <= r_i and l_i <= r_i, we need l_i <= r_j.
    // So interval j is covered if l_j <= l_i and l_i <= r_j.
    //
    // For the greedy to be O(n log n), we can use a segment tree or similar.
    // But for n <= 1e5, O(n^2) might be too slow.
    // Let me use a different approach: process from left to right.
    //
    // Actually, let me use the observation that we process from right to left,
    // and for each point, we skip all intervals with r >= pt (since they're already covered
    // or will be covered by a later point).
    //
    // Wait, processing from right to left: interval i has r_i. We place at l_i.
    // Interval j (j < i) has r_j <= r_i. It's covered if l_j <= l_i <= r_j.
    // If l_i > r_j, it's not covered. Since r_j <= r_i and l_i <= r_i,
    // l_i > r_j means r_j < l_i <= r_i. So interval j has r_j < l_i.
    //
    // Since intervals are sorted by r, all intervals with r < l_i are NOT covered.
    // So we can use binary search to find the rightmost interval with r < l_i,
    // and skip all intervals from 0 to that index.
    
    long long totalCost = 0;
    int i = n - 1;
    while (i >= 0) {
        long long pt = intervals[i].first;
        totalCost += pt;
        // Find rightmost interval with r < pt (not covered)
        // Binary search: find largest j such that intervals[j].second < pt
        int lo = 0, hi = i - 1, j = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (intervals[mid].second < pt) { j = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        i = j;
    }
    
    cout << totalCost << "\n";
    return 0;
}
