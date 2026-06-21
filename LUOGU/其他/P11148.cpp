#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        int m; cin >> m;
        vector<long long> b(m);
        for (int i = 0; i < m; i++) cin >> b[i];
        // Sort both in descending order
        sort(a.begin(), a.end(), greater<long long>());
        sort(b.begin(), b.end(), greater<long long>());
        // We want to maximize the sum of values that are NOT the first of their type.
        // Equivalent to: total sum of all values - sum of first-of-type values.
        // We want to minimize the sum of first-of-type values.
        // There are (number of type switches + 1) first-of-type values.
        // Minimum first-of-type values: 2 (one for each type).
        // But we might have 0 or 1 types.
        // The sum of first-of-type values = sum of one value from each contiguous block.
        // To minimize: use the smallest values as first-of-type.
        // But the structure is constrained by the interleaving.
        //
        // Actually, let me think differently.
        // In any interleaving, there are some "transitions" between types.
        // Each contiguous block of same-type contributes the first value (no happiness).
        // All other values contribute their full value (happiness).
        // Total happiness = total_sum - sum of first values of each block.
        // To maximize happiness = minimize sum of first values.
        //
        // With k blocks total (some A, some B), we need at least 2 blocks (unless one type is empty).
        // The first values are the first elements of each block.
        // To minimize: make the first values as small as possible.
        //
        // Optimal strategy: group all positive values of each type together,
        // and put negative values at the start of blocks (as first values).
        //
        // Actually, the optimal is more nuanced. Let me use a different approach.
        // For each type, the values in order contribute:
        // - First occurrence: 0 happiness
        // - Subsequent: value happiness
        // So for type A: happiness = sum of all A values - (first A value in its block).
        // For type B: similarly.
        // Total = total_sum - (first A value) - (first B value).
        // To maximize: minimize (first A value + first B value).
        // Use min of A values for first A, min of B values for first B.
        // But we need at least one of each type in the interleaving.
        // If n == 0: happiness from B = sum(B) - min(B).
        // If m == 0: happiness from A = sum(A) - min(A).
        // If both > 0: happiness = total - min(A) - min(B).
        //
        // Wait, this assumes each type has exactly one block. Is that optimal?
        // If we split a type into multiple blocks, we add more first-values (worse).
        // So yes, one block per type is optimal.
        //
        // But what about the ordering? A-block first or B-block first?
        // It doesn't matter for the sum of first values.
        //
        // So: happiness = sum(A) + sum(B) - min_value(A) - min_value(B).
        // But we also need to handle negative values carefully.
        // If all A values are negative: min(A) is the most negative.
        // Using it as first: we lose less (since it's already negative).
        // Actually, the first value contributes 0 happiness, so we "lose" its value.
        // If it's negative, we actually gain by not counting it.
        //
        // Hmm, let me reconsider. The problem says:
        // "如果 Yazid 在其之前吃的零食与其类型相同，则 Yazid 会增加当前零食妙值的快乐度"
        // So happiness = sum of values that have a same-type predecessor.
        // First of each block: no happiness (contributes 0).
        // Others: contribute their value.
        // Total happiness = total_sum - sum_of_first_values.
        // To maximize: minimize sum_of_first_values.
        //
        // With one block per type: sum_of_first_values = first_A + first_B.
        // first_A = the value placed at the start of the A block.
        // We can choose which A value is first by reordering within the block.
        // To minimize: use the smallest A value as first.
        // Similarly for B.
        //
        // So: happiness = total_sum - min(A) - min(B).
        // If n == 0: happiness = sum(B) - min(B).
        // If m == 0: happiness = sum(A) - min(A).
        // If both > 0: happiness = total_sum - min(A) - min(B).
        //
        // But wait, what if we have multiple blocks? Could that help?
        // If we split A into 2 blocks: sum_of_first_values increases by another A value.
        // So it's always worse. One block per type is optimal.
        //
        // Special case: if n == 0 and m == 0: happiness = 0.
        
        long long total = 0;
        for (long long x : a) total += x;
        for (long long x : b) total += x;
        
        long long ans;
        if (n == 0 && m == 0) {
            ans = 0;
        } else if (n == 0) {
            // One block of B. First value = min(B). Others contribute.
            long long minB = b[0];
            for (long long x : b) minB = min(minB, x);
            ans = total - minB;
        } else if (m == 0) {
            long long minA = a[0];
            for (long long x : a) minA = min(minA, x);
            ans = total - minA;
        } else {
            long long minA = a[0], minB = b[0];
            for (long long x : a) minA = min(minA, x);
            for (long long x : b) minB = min(minB, x);
            ans = total - minA - minB;
        }
        cout << ans << "\n";
    }
    return 0;
}
