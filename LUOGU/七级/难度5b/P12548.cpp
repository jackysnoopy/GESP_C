#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> x(2 * n), y(2 * n);
    for (int i = 0; i < 2 * n; i++) {
        cin >> x[i] >> y[i];
    }
    
    // Manhattan distance = |x1-x2| + |y1-y2|
    // Since y is 0 or 1, distance is either |x1-x2| or |x1-x2|+1
    // We want to minimize the maximum distance over all pairs
    
    // Binary search on the answer
    long long lo = 0, hi = 2e9;
    
    auto check = [&](long long mid) -> bool {
        // Try to pair all points such that each pair has distance <= mid
        // Since y is 0 or 1, we need to handle pairs carefully
        
        // Count points on y=0 and y=1
        vector<long long> zero, one;
        for (int i = 0; i < 2 * n; i++) {
            if (y[i] == 0) zero.push_back(x[i]);
            else one.push_back(x[i]);
        }
        
        sort(zero.begin(), zero.end());
        sort(one.begin(), one.end());
        
        int nz = zero.size(), no = one.size();
        
        // We need to pair all 2n points
        // Each pair can be (0,0), (1,1), or (0,1)
        // (0,0) or (1,1) pair: distance = |xi - xj|
        // (0,1) pair: distance = |xi - xj| + 1
        
        // For a given mid, we need to check if we can pair all points
        // such that max distance <= mid
        
        // This is complex. Let's think differently.
        // For (0,1) pairs: |xi - xj| + 1 <= mid, so |xi - xj| <= mid - 1
        // For (0,0) or (1,1) pairs: |xi - xj| <= mid
        
        // We need to find a perfect matching where all edges satisfy the constraint
        
        // Simple greedy: try to match as many cross-type pairs as possible
        // Then match remaining within type
        
        int used_z = 0, used_o = 0;
        int cross_pairs = 0;
        
        // Try to match cross-type pairs
        int i = 0, j = 0;
        vector<bool> matched_z(nz, false), matched_o(no, false);
        
        while (i < nz && j < no) {
            if (abs(zero[i] - one[j]) + 1 <= mid) {
                matched_z[i] = matched_o[j] = true;
                cross_pairs++;
                i++;
                j++;
            } else if (zero[i] < one[j]) {
                i++;
            } else {
                j++;
            }
        }
        
        // Count unmatched
        int unmatched_z = 0, unmatched_o = 0;
        for (int k = 0; k < nz; k++) if (!matched_z[k]) unmatched_z++;
        for (int k = 0; k < no; k++) if (!matched_o[k]) unmatched_o++;
        
        // Check if unmatched can be paired within type
        // For within-type pairing, we need consecutive elements to have distance <= mid
        
        auto can_pair_within = [&](const vector<long long>& v, bool is_zero) -> bool {
            int m = v.size();
            if (m == 0) return true;
            // Greedy: pair consecutive elements
            int cnt = 0;
            for (int k = 0; k < m - 1; k += 2) {
                if (v[k + 1] - v[k] <= mid) cnt++;
                else return false;
            }
            return cnt == m / 2;
        };
        
        // Extract unmatched elements
        vector<long long> uz, uo;
        for (int k = 0; k < nz; k++) if (!matched_z[k]) uz.push_back(zero[k]);
        for (int k = 0; k < no; k++) if (!matched_o[k]) uo.push_back(one[k]);
        
        if (uz.size() % 2 != 0 || uo.size() % 2 != 0) return false;
        
        return can_pair_within(uz, true) && can_pair_within(uo, false);
    };
    
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    
    cout << lo << endl;
    
    return 0;
}
