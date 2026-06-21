#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    // Maximize sum of |a[p[i]] - a[p[i+1]]| for permutation p.
    // Optimal: interleave small and large values.
    // For sorted a: put largest, smallest, 2nd largest, 2nd smallest, ...
    // Or: the maximum is 2 * sum of top half - 2 * sum of bottom half (for even n).
    // For odd n: the middle element contributes 0 or is counted once.
    // Actually, the formula: sort ascending. 
    // For even n: ans = 2 * sum(a[n/2..n-1]) - 2 * sum(a[0..n/2-1]) - a[n/2-1] + a[n/2]
    // Hmm, let me just compute it directly.
    // Optimal arrangement: sort, then arrange as a[0], a[n-1], a[1], a[n-2], ...
    // Or: the answer is 2 * sum of (a[i] - a[i-1]) for every other pair.
    // Simpler: sort ascending. The answer is:
    // For even n: 2*(a[n-1]+a[n-2]+...+a[n/2]) - 2*(a[0]+a[1]+...+a[n/2-1])
    //   except the boundary terms.
    // Actually just use the formula: after sorting, the max sum of abs differences
    // for a permutation is:
    // Sort a ascending. 
    // ans = 0;
    // For each element, it contributes to at most 2 adjacent differences.
    // The largest elements should appear in the middle (contributing twice).
    // The smallest elements should also appear in the middle.
    // The boundary elements contribute once.
    // Optimal: alternate high-low-high-low.
    // For sorted a: a[0] a[n-1] a[1] a[n-2] a[2] ...
    // Differences: a[n-1]-a[0], a[n-1]-a[1], a[n-2]-a[1], a[n-2]-a[2], ...
    // 
    // Formula for max sum of |adjacent differences| in a permutation:
    // Sort ascending. ans = 0.
    // For i from 0 to n/2-1: ans += a[n-1-i] - a[i] (for both left and right neighbors).
    // But boundary elements are counted once.
    // Actually: ans = 2 * sum(a[n/2..n-1]) - 2 * sum(a[0..n/2-1]) 
    //   - (for odd n: subtract middle, for even: adjust boundaries)
    //
    // Let me just use the known formula:
    // Sort a ascending.
    // For even n: ans = 2 * (sum of top n/2) - 2 * (sum of bottom n/2)
    //   - a[n/2-1] + a[n/2] ... no, that's not right either.
    //
    // Known result: for a sorted array a[0] <= a[1] <= ... <= a[n-1],
    // the maximum sum of |p[i] - p[i+1]| over all permutations is:
    // For even n: 2 * sum_{i=n/2}^{n-1} a[i] - 2 * sum_{i=0}^{n/2-1} a[i]
    // For odd n: same formula, but the middle element a[n/2] is subtracted once
    //   (it appears at a boundary).
    // Actually for odd n: 2 * sum_{i=(n+1)/2}^{n-1} a[i] - 2 * sum_{i=0}^{(n-3)/2} a[i]
    //   - a[(n-1)/2] ... hmm, this is getting complicated.
    //
    // Let me just use the direct formula:
    // For sorted a, the max sum = sum of all elements * 2 - min - max - ...
    // Actually, the known result is:
    // Arrange as: a[0], a[n-1], a[1], a[n-2], a[2], ...
    // The sum = (a[n-1]-a[0]) + (a[n-1]-a[1]) + (a[n-2]-a[1]) + (a[n-2]-a[2]) + ...
    // For even n: each a[i] for i < n/2 appears twice as a subtracted term.
    //             each a[i] for i >= n/2 appears twice as an added term.
    //             But the boundary terms appear once.
    //             Actually: a[0] appears once (subtracted), a[n-1] appears once (added).
    //             a[1] appears twice (subtracted), a[n-2] appears twice (added). Etc.
    //             
    // For even n=4, sorted [1,2,3,4]:
    // Arrange: 1,4,2,3. Sum = 3+2+1 = 6. But max is 7 (from sample).
    // Arrange: 2,4,1,3. Sum = 2+3+2 = 7. Yes!
    // 
    // So the arrangement matters. Let me think more carefully.
    // For [1,2,3,4]: optimal is 2,4,1,3 with sum 7.
    // Differences: |4-2|=2, |4-1|=3, |3-1|=2. Total=7.
    //
    // Known result for maximum sum of absolute differences in a permutation:
    // Sort a ascending. 
    // For even n: ans = 2 * (a[n-1] + a[n-2] + ... + a[n/2]) - 2 * (a[0] + a[1] + ... + a[n/2-1])
    //   - a[n/2-1] + a[n/2] ... no.
    //
    // Actually, the formula is:
    // Sort ascending. For each position i in the permutation:
    // If i is "interior" (not first or last), the element at position i contributes
    // to two differences. If it's a large element, it contributes positively.
    // If it's a small element, it contributes negatively.
    // Optimal: put large elements at interior positions, small elements at boundaries.
    // But we have n-2 interior positions and 2 boundary positions.
    // For n=4: 2 interior positions. Put a[2]=3 and a[3]=4 there.
    // Boundaries: a[0]=1 and a[1]=2.
    // Sum = (a[3]-a[0]) + (a[3]-a[1]) + (a[2]-a[1]) = 3+2+1 = 6? No.
    // Wait, the permutation is [1, 4, 3, 2] or something.
    // [1, 4, 3, 2]: |4-1|+|3-4|+|2-3| = 3+1+1 = 5.
    // [2, 4, 1, 3]: |4-2|+|4-1|+|3-1| = 2+3+2 = 7.
    //
    // Hmm, the arrangement [2,4,1,3] doesn't follow the "large in interior" pattern.
    // Let me think about it differently.
    //
    // For the permutation [p1, p2, ..., pn], the sum is:
    // |a[p2]-a[p1]| + |a[p3]-a[p2]| + ... + |a[pn]-a[pn-1]|
    // = sum of absolute differences of consecutive elements.
    //
    // This is the "maximum traveling salesman" problem on a line.
    // For points on a line (sorted), the maximum TSP is:
    // Arrange as: 1, n, 2, n-1, 3, n-2, ...
    // The sum = (a[n]-a[1]) + (a[n]-a[2]) + (a[n-1]-a[2]) + (a[n-1]-a[3]) + ...
    //
    // For sorted [1,2,3,4]:
    // 2,4,1,3: |4-2|+|4-1|+|3-1| = 2+3+2 = 7.
    // Or: 1,3,2,4: |3-1|+|3-2|+|4-2| = 2+1+2 = 5.
    // Or: 3,1,4,2: |1-3|+|4-1|+|2-4| = 2+3+2 = 7.
    //
    // The formula: for sorted a, the maximum sum is:
    // For even n: 2 * sum(a[n/2..n-1]) - 2 * sum(a[0..n/2-1]) - a[n/2-1] + a[n/2]
    // Wait, let me just compute for [1,2,3,4]:
    // 2 * (3+4) - 2 * (1+2) = 14 - 6 = 8. But answer is 7!
    //
    // Hmm, that formula is wrong. Let me look up the correct formula.
    //
    // For sorted a[0] <= a[1] <= ... <= a[n-1]:
    // Maximum sum of |a[p[i]] - a[p[i+1]]| over all permutations p:
    // For even n: 2 * sum_{i=n/2}^{n-1} a[i] - 2 * sum_{i=0}^{n/2-1} a[i] - a[n/2] + a[n/2-1]
    //   = 2 * sum(a[n/2..n-1]) - 2 * sum(a[0..n/2-1]) + a[n/2-1] - a[n/2]
    // For [1,2,3,4]: 2*(3+4) - 2*(1+2) + 2 - 3 = 14 - 6 + 2 - 3 = 7. Correct!
    //
    // For odd n: 2 * sum(a[(n+1)/2..n-1]) - 2 * sum(a[0..(n-3)/2]) - a[(n-1)/2]
    //   = 2 * sum(a[(n+1)/2..n-1]) - 2 * sum(a[0..(n-3)/2]) - a[(n-1)/2]
    // For [1,2,3,4,5]: 2*(4+5) - 2*(1+2) - 3 = 18 - 6 - 3 = 9.
    // But sample says 11!
    //
    // Hmm, let me recheck. For [1,2,3,4,5], optimal arrangement:
    // 3,5,1,4,2: |5-3|+|5-1|+|4-1|+|4-2| = 2+4+3+2 = 11. Yes!
    // 2,5,1,4,3: |5-2|+|5-1|+|4-1|+|4-3| = 3+4+3+1 = 11.
    //
    // So my formula is wrong for odd n. Let me reconsider.
    //
    // Actually, the correct formula for maximum sum of absolute differences:
    // Sort a ascending.
    // For even n=2k: ans = 2*(a[k]+a[k+1]+...+a[2k-1]) - 2*(a[0]+a[1]+...+a[k-1]) - a[k-1] + a[k]
    // Wait, I got 7 for n=4 with this. Let me recheck.
    // For n=4, k=2: 2*(a[2]+a[3]) - 2*(a[0]+a[1]) - a[1] + a[2] = 2*(3+4) - 2*(1+2) - 2 + 3 = 14-6-2+3 = 9.
    // That's 9, not 7! Wrong again.
    //
    // OK let me just compute it directly.
    // For the arrangement [2,4,1,3] with [1,2,3,4]:
    // |4-2|+|4-1|+|3-1| = 2+3+2 = 7.
    // 
    // For the arrangement [3,5,1,4,2] with [1,2,3,4,5]:
    // |5-3|+|5-1|+|4-1|+|4-2| = 2+4+3+2 = 11.
    //
    // Let me think about it as: each element appears in the sum based on its neighbors.
    // Element at position i (not first/last) contributes +a[i] for the larger neighbor
    // and -a[i] for the smaller neighbor. Net: depends on which is larger.
    //
    // Actually, for the maximum sum, we want each element to be counted as +a[i] twice
    // (once for each neighbor being smaller) or -a[i] twice (once for each neighbor being larger).
    // Large elements should have both neighbors smaller (counted as +2*a[i]).
    // Small elements should have both neighbors larger (counted as -2*a[i]).
    // Boundary elements are counted once.
    //
    // For n elements, we have n-2 interior positions and 2 boundary positions.
    // We want to put the (n-2) largest elements at interior positions (counted twice)
    // and the 2 smallest at boundaries (counted once).
    // Wait, that gives: 2*(a[2]+a[3]+...+a[n-1]) - 2*(nothing, since small elements are at boundaries)
    //   - a[0] - a[1] (boundary elements counted once, subtracted).
    // For [1,2,3,4]: 2*(3+4) - 1 - 2 = 14 - 3 = 11. But answer is 7!
    //
    // That's wrong because we can't make ALL interior elements "large with both neighbors smaller".
    // The arrangement constrains which elements can be interior.
    //
    // OK I think the issue is that the formula depends on the specific arrangement.
    // Let me just use the known result: for sorted a, the maximum sum is:
    // For even n: sum_{i=0}^{n/2-1} (a[n-1-i] - a[i]) * 2 - (a[n/2] - a[n/2-1])
    // For odd n: sum_{i=0}^{(n-1)/2-1} (a[n-1-i] - a[i]) * 2
    //
    // For [1,2,3,4] (n=4, even): (a[3]-a[0])*2 + (a[2]-a[1])*2 - (a[2]-a[1]) = (4-1)*2 + (3-2)*2 - (3-2) = 6+2-1 = 7. Correct!
    // Wait, that's: 2*(a[3]-a[0]) + 2*(a[2]-a[1]) - (a[2]-a[1]) = 2*(a[3]-a[0]) + (a[2]-a[1]) = 6+1 = 7. Correct!
    //
    // For [1,2,3,4,5] (n=5, odd): 2*(a[4]-a[0]) + 2*(a[3]-a[1]) = 2*(5-1) + 2*(4-2) = 8+4 = 12. But answer is 11!
    //
    // Hmm, still wrong. Let me try another formula.
    // For [1,2,3,4,5]: the arrangement [3,5,1,4,2] gives 11.
    // Let me check [1,5,2,4,3]: |5-1|+|5-2|+|4-2|+|4-3| = 4+3+2+1 = 10.
    // [2,5,1,4,3]: |5-2|+|5-1|+|4-1|+|4-3| = 3+4+3+1 = 11.
    // [1,5,2,4,3]: 10.
    // [3,5,1,4,2]: 11.
    // [2,5,1,4,3]: 11.
    // [1,4,2,5,3]: |4-1|+|4-2|+|5-2|+|5-3| = 3+2+3+2 = 10.
    // [3,1,5,2,4]: |1-3|+|5-1|+|5-2|+|4-2| = 2+4+3+2 = 11.
    //
    // So the max is 11 for n=5.
    //
    // Let me try: for sorted a, the max sum is:
    // For odd n=2k+1: 2*sum(a[k+1..2k]) - 2*sum(a[0..k-1]) + a[k] - a[k-1]... no.
    //
    // Actually, let me just compute it as:
    // Sort ascending. Arrange as: a[k], a[n-1], a[k-1], a[n-2], ..., a[0], a[k+1]
    // where k = n/2 (or n/2 for even, (n-1)/2 for odd).
    // Then compute the sum of absolute differences.
    //
    // For [1,2,3,4] (k=2): a[2]=3, a[3]=4, a[1]=2, a[0]=1. Arrange: 3,4,2,1.
    // |4-3|+|2-4|+|1-2| = 1+2+1 = 4. Not optimal.
    //
    // OK let me just implement the formula directly.
    // For sorted a, the maximum sum of absolute differences in a permutation is:
    // 
    // I'll use the known result from competitive programming:
    // Sort a ascending.
    // For even n: ans = 2 * sum(a[n/2..n-1]) - 2 * sum(a[0..n/2-1])
    // For odd n: ans = 2 * sum(a[(n+1)/2..n-1]) - 2 * sum(a[0..(n-3)/2]) - a[(n-1)/2]
    // Wait, for [1,2,3,4,5] (n=5): 2*(4+5) - 2*(1+2) - 3 = 18-6-3 = 9. But answer is 11.
    //
    // Let me try yet another formula:
    // For odd n: ans = 2 * sum(a[(n+1)/2..n-1]) - 2 * sum(a[0..(n-3)/2])
    //   = 2*(4+5) - 2*(1+2) = 18-6 = 12. Still wrong.
    //
    // Hmm, let me look at the problem from scratch.
    // For sorted a, the maximum sum is achieved by the arrangement:
    // a[0], a[n-1], a[1], a[n-2], a[2], a[n-3], ...
    // For [1,2,3,4,5]: 1,5,2,4,3. Sum = 4+3+2+1 = 10.
    // Not optimal (11 is better).
    //
    // Alternative: a[n-1], a[0], a[n-2], a[1], a[n-3], ...
    // For [1,2,3,4,5]: 5,1,4,2,3. Sum = 4+3+2+1 = 10. Same.
    //
    // Another: a[2], a[4], a[0], a[3], a[1] = 3,5,1,4,2. Sum = 2+4+3+2 = 11.
    // This is the "center-out" arrangement.
    //
    // For the center-out arrangement:
    // Start from the middle, alternate going to the extremes.
    // For sorted [1,2,3,4,5]: start at 3, go to 5, go to 1, go to 4, go to 2.
    // Sum = |5-3|+|5-1|+|4-1|+|4-2| = 2+4+3+2 = 11.
    //
    // Formula for center-out:
    // For sorted a[0..n-1], middle index m = (n-1)/2.
    // Arrange: a[m], a[n-1], a[0], a[n-2], a[1], a[n-3], ...
    // Sum = (a[n-1]-a[m]) + (a[n-1]-a[0]) + (a[n-2]-a[0]) + (a[n-2]-a[1]) + ...
    //
    // For even n, m = n/2-1 or n/2.
    // For [1,2,3,4] (n=4, m=1): a[1]=2, a[3]=4, a[0]=1, a[2]=3. Arrange: 2,4,1,3.
    // Sum = |4-2|+|4-1|+|3-1| = 2+3+2 = 7. Correct!
    //
    // For [1,2,3,4,5] (n=5, m=2): a[2]=3, a[4]=5, a[0]=1, a[3]=4, a[1]=2. Arrange: 3,5,1,4,2.
    // Sum = 2+4+3+2 = 11. Correct!
    //
    // For [1,2,3,4,5,6,7,8,9,10] (n=10, m=4): a[4]=5, a[9]=10, a[0]=1, a[8]=9, a[1]=2, a[7]=8, a[2]=3, a[6]=7, a[3]=4, a[5]=6.
    // Arrange: 5,10,1,9,2,8,3,7,4,6.
    // Sum = 5+9+8+7+6+5+4+3+1+2 = 50. But sample says 49.
    //
    // Hmm, 50 != 49. Let me recompute.
    // |10-5|=5, |10-1|=9, |9-1|=8, |9-2|=7, |8-2|=6, |8-3|=5, |7-3|=4, |7-4|=3, |6-4|=2.
    // Sum = 5+9+8+7+6+5+4+3+2 = 49. I miscounted. 5+9=14, +8=22, +7=29, +6=35, +5=40, +4=44, +3=47, +2=49. Correct!
    //
    // So the center-out arrangement works. Let me implement it.
    
    vector<long long> b(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<long long> perm;
    int m = (n - 1) / 2;
    perm.push_back(b[m]);
    int lo = 0, hi = n - 1;
    bool goHigh = true;
    for (int i = 0; i < n - 1; i++) {
        if (goHigh) { perm.push_back(b[hi]); hi--; }
        else { perm.push_back(b[lo]); lo++; }
        goHigh = !goHigh;
    }
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        ans += llabs(perm[i] - perm[i-1]);
    }
    cout << ans << "\n";
    return 0;
}
