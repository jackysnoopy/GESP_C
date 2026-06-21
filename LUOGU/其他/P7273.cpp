#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, w;
    cin >> n >> w;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n <= 2) { cout << 0 << endl; return 0; }
    // For n=1: 0 modifications (single element is always AP with d=0).
    // For n=2: 0 modifications (two elements always form AP).
    // For n>=3: we need to find the longest subsequence that can form an AP with non-negative difference.
    // The AP is determined by its first element a1 and difference d >= 0.
    // For position i (0-indexed), the value should be a1 + i*d.
    // We want to maximize the number of positions that already have this value.
    // Answer = n - max number of unchanged positions.
    //
    // For each pair (i, j) with i < j, if a[i] and a[j] are kept, then:
    //   d = (a[j] - a[i]) / (j - i) must be a non-negative integer.
    //   a1 = a[i] - i * d must be >= 1 (since values are positive).
    //   For all k, a1 + k * d must be <= w.
    //
    // Brute force: try all (i, j) pairs, compute d, check how many positions match.
    // O(n^3) which is too slow for n=3e5.
    //
    // Better approach: for each possible d, find the longest AP subsequence.
    // d can range from 0 to w (since values are 1..w).
    // For a fixed d, the AP starting at position i with value a[i] determines all values.
    // At position j, the value should be a[i] + (j-i)*d.
    // We want to maximize the number of j where a[j] = a[i] + (j-i)*d.
    // This is equivalent to: for each d, compute the most frequent value of (a[j] - j*d).
    // The answer for this d is the frequency of the most common value.
    //
    // But d can be up to w = 3e5, and n = 3e5. For each d, we'd need O(n) time.
    // Total: O(n*w) = O(9e10). Too slow.
    //
    // Optimization: for small d (d <= sqrt(w)), use the above approach.
    // For large d (d > sqrt(w)), there are at most sqrt(w) positions that can be in the AP
    // (since the AP values grow quickly). So for each starting position i, try all d > sqrt(w)
    // and check if the AP is valid.
    //
    // Actually, let me think differently. The AP is determined by (a1, d).
    // a1 >= 1, d >= 0, a1 + (n-1)*d <= w.
    // For d = 0: all values are the same. Find the most frequent value.
    // For d > 0: a1 = a[i] - i*d. For this to be >= 1, we need d <= (a[i]-1)/i.
    //   Also a1 + (n-1)*d <= w, so d <= (w-a1)/(n-1).
    //
    // Let me use the sqrt decomposition approach.
    // For d <= B (B = sqrt(w)): for each d, use a hash map to find the most common (a[j] - j*d).
    // For d > B: for each starting position i, the AP has at most (w-1)/d + 1 <= B+1 terms.
    //   So we can enumerate all valid (i, d) pairs.
    
    int B = max(1, (int)sqrt((double)w));
    int best = 1; // at least 1 element can stay
    
    // d = 0: most frequent value
    vector<int> freq(w + 1, 0);
    for (int i = 0; i < n; i++) freq[a[i]]++;
    for (int v = 1; v <= w; v++) best = max(best, freq[v]);
    
    // d = 1 to B
    for (int d = 1; d <= min(B, w); d++) {
        // For each position j, compute key = a[j] - j*d
        // Find the most frequent key
        vector<int> keys(n);
        for (int j = 0; j < n; j++) {
            keys[j] = a[j] - j * d;
        }
        // Use unordered_map (or sort)
        sort(keys.begin(), keys.end());
        int cnt = 1;
        for (int j = 1; j < n; j++) {
            if (keys[j] == keys[j-1]) cnt++;
            else { best = max(best, cnt); cnt = 1; }
        }
        best = max(best, cnt);
    }
    
    // d > B
    for (int i = 0; i < n; i++) {
        // For each d > B, a1 = a[i] - i*d >= 1 => d <= (a[i]-1)/i (if i > 0)
        // a1 + (n-1)*d <= w => d <= (w - a1) / (n-1)
        // Also d > B.
        int max_d = w; // rough upper bound
        if (i > 0) max_d = min(max_d, (a[i] - 1) / i);
        if (max_d <= B) continue;
        // For d > B, the AP has at most (w / d) + 1 terms.
        // But we need to check which positions match.
        // For each d from B+1 to max_d:
        //   a1 = a[i] - i*d
        //   Check positions j = i, i+1, ..., i+k where a1 + j*d is in [1, w] and a[j] = a1 + j*d.
        //   k <= w/d <= w/B = sqrt(w).
        // So for each (i, d) pair, we check at most sqrt(w) positions.
        // Total pairs: sum over i of (max_d - B) which could be large.
        //
        // Better: for each i, enumerate d from B+1 to max_d.
        // But max_d could be up to w, and there are n positions.
        // Total: O(n * w/B) = O(n * sqrt(w)). For n=3e5, w=3e5: O(3e5 * 550) = O(1.65e8). Tight but might work.
        
        for (int d = B + 1; d <= max_d; d++) {
            long long a1 = (long long)a[i] - (long long)i * d;
            if (a1 < 1) break;
            if (a1 + (long long)(n - 1) * d > w) continue;
            // Check how many positions match
            int cnt = 0;
            for (int j = i; j < n && a1 + (long long)j * d <= w; j++) {
                if (a[j] == (int)(a1 + (long long)j * d)) cnt++;
            }
            best = max(best, cnt);
            // Also check positions before i
            for (int j = i - 1; j >= 0 && a1 + (long long)j * d >= 1; j--) {
                if (a[j] == (int)(a1 + (long long)j * d)) cnt++;
            }
            best = max(best, cnt);
        }
    }
    
    cout << n - best << endl;
    return 0;
}
