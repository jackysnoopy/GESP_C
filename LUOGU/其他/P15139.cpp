#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        string s;
        cin >> s;
        // Simulate expansion from (x,y) using s[l-1..r-1]
        // BFS simulation on the grid
        // But grid can be large. However, after processing, 
        // the reachable region is bounded by Manhattan distance for '4' and Chebyshev for '8'.
        //
        // Count 4s and 8s in the substring.
        int cnt4 = 0, cnt8 = 0;
        for (int i = l - 1; i < r; i++) {
            if (s[i] == '4') cnt4++;
            else cnt8++;
        }
        // After processing:
        // '8' expands Chebyshev by 1 each time.
        // '4' expands Manhattan by 1 each time.
        // Combined: the reachable region after processing all characters depends on order.
        //
        // Actually for this problem with nm <= 200000, the queries are on substrings of s.
        // We need to answer: is (0,0) reachable from (x,y)?
        //
        // Key insight: after processing the entire sequence:
        // - First, all '8' operations expand the Chebyshev radius.
        // - Then '4' operations expand the Manhattan radius.
        // But order matters.
        //
        // Let me think about it differently:
        // After processing all 8s: Chebyshev radius = cnt8.
        // After processing all 4s: Manhattan radius increases by cnt4.
        // But interleaving 4s and 8s is more complex.
        //
        // For the problem to work, the final region must be:
        // Cells with Chebyshev dist <= cnt8 AND Manhattan dist <= cnt8*2 + cnt4?
        // Or: cells where max(|dx|,|dy|) <= cnt8 + cnt4 and min(|dx|,|dy|) <= cnt8?
        //
        // Actually: 8 expands all 8 directions (Chebyshev +1).
        // 4 expands 4 directions (Manhattan +1, but only orthogonal).
        // After k8 '8' ops and k4 '4' ops:
        // - Chebyshev expansion from '8': radius k8
        // - Additional Manhattan expansion from '4': adds k4 to Manhattan radius
        // But '4' only expands orthogonally. After '8' creates a diamond+square,
        // '4' extends it by Manhattan distance.
        //
        // The final region: all cells reachable from (0,0) where:
        //   max(|dx|,|dy|) <= k8 + k4 AND |dx| + |dy| <= k8*2 + k4?
        // No, this doesn't account for order.
        //
        // For the problem to be solvable with nm <= 200000, let me try BFS with bounded region.
        // The max distance from origin is at most (cnt4 + cnt8).
        // With nm <= 200000, this is feasible.
        //
        // But q can be large. Each query needs BFS. With nm <= 200000 total characters,
        // and the region size bounded, this should be OK.
        //
        // Actually, let me just simulate for each query.
        // The reachable region after all operations is at most size O((cnt4+cnt8)^2).
        // For nm <= 200000, worst case cnt4+cnt8 = 200000, region = 4*10^10. Too large.
        //
        // For difficulty 2, there must be a formula. Let me think:
        // 8 expands Chebyshev by 1. 4 expands Manhattan by 1.
        // If we process all 8s first then all 4s:
        //   After 8s: diamond of Chebyshev radius k8 = {(x,y): max(|x|,|y|) <= k8}
        //   After 4s: Manhattan expansion of k4 from that region.
        //   A cell (a,b) is reachable if there exists (x,y) with max(|x|,|y|) <= k8
        //   and |a-x| + |b-y| <= k4.
        //   Equivalently: min over (x,y) in diamond of |a-x|+|b-y| <= k4.
        //   The minimum Manhattan distance from (a,b) to the diamond is:
        //   max(0, max(|a|,|b|) - k8) + max(0, |a| + |b| - k8 - max(|a|,|b|))
        //   Hmm, this is getting complex.
        //
        // For simplicity, let me use a different approach:
        // The distance metric after k8 '8' ops and k4 '4' ops:
        // A cell (a,b) is reachable iff it can be reached by alternating 8 and 4 operations.
        // This is equivalent to: there exists a path from (0,0) to (a,b) using at most k8 
        // Chebyshev steps and k4 Manhattan steps (in any order).
        //
        // The Chebyshev distance from (0,0) to (a,b) is max(|a|,|b|).
        // The Manhattan distance is |a|+|b|.
        // 
        // After k8 Chebyshev steps and k4 Manhattan steps:
        // We need max(|a|,|b|) <= k8 + k4 (each step covers at most 1 in Chebyshev)
        // AND |a|+|b| <= k8*2 + k4 (each 8 covers 2 in Manhattan, each 4 covers 1)
        // Wait, an 8 step increases both |dx| and |dy| by at most 1 each, so Manhattan increases by 2.
        // A 4 step increases Manhattan by 1.
        // So max Manhattan = k8*2 + k4.
        //
        // But the condition for reachability isn't just about max distances.
        // It's about whether (a,b) is in the reachable set after processing all ops.
        //
        // I think the answer is: (a,b) is reachable iff:
        //   max(|a|,|b|) <= k8 + k4
        //   AND |a| + |b| <= 2*k8 + k4
        //   AND |a| + |b| >= |max(|a|,|b|) - k8| ... no this is getting circular.
        //
        // Let me just go with BFS for small cases and a formula for large.
        // Actually for nm <= 200000, and the query region bounded, I'll use BFS.
        // But the region can be up to 200000 in each direction...
        //
        // Let me try a formula approach. The reachable region after k8 '8' and k4 '4':
        // Process all 8 first: diamond of Chebyshev radius k8.
        // Then process all 4: Manhattan expansion by k4.
        // But order matters because 4 only expands orthogonally.
        //
        // Actually I think the answer is independent of order:
        // The region is {(a,b) : max(|a|,|b|) <= k8+k4 AND |a|+|b| <= 2*k8+k4}
        // AND |a|+|b| >= k8 (since 8 expands in all directions)
        // Hmm not sure.
        //
        // Let me try: for (x,y) to be reachable from (0,0):
        // We need distance = |x|+|y| (Manhattan)
        // Using k8 '8' ops and k4 '4' ops:
        // Each 8 reduces Manhattan distance by up to 2 (moving diagonally toward target).
        // Each 4 reduces Manhattan distance by up to 1.
        // We need 2*k8 + k4 >= |x|+|y|.
        // Also need Chebyshev distance: max(|x|,|y|) <= k8 + k4.
        // Also need: the 8 ops can't overshoot in Chebyshev.
        //
        // I think the condition is:
        //   d_manhattan = |x|+|y|
        //   d_chebyshev = max(|x|,|y|)
        //   d_manhattan <= 2*k8 + k4
        //   d_chebyshev <= k8 + k4
        //   AND d_manhattan >= d_chebyshev (always true)
        //   AND ... some parity constraint?
        //
        // Actually the key constraint might be simpler:
        // After k8 '8' ops: we're in a diamond of Chebyshev radius k8.
        // The "excess" Manhattan that can't be covered by 8 ops: d_manhattan - 2*k8 (if positive).
        // This excess must be covered by 4 ops: d_manhattan - 2*k8 <= k4.
        // Also: d_chebyshev <= k8 + k4.
        // And: if d_manhattan < k8: we might be "inside" the diamond, need 4 ops to reach?
        //   Actually if d_manhattan <= 2*k8, the 8 ops can reach it (Chebyshev <= k8).
        //   Wait: Chebyshev <= k8 is equivalent to max(|x|,|y|) <= k8.
        //   If both conditions are met, it's reachable.
        //
        // Let me just check with a simple case:
        // k8=0, k4=1: can reach (0,1),(1,0),(0,-1),(-1,0). Manhattan=1, Chebyshev=1.
        // Condition: 1 <= 0+1=1 ✓, 1 <= 0+1=1 ✓. OK.
        // k8=1, k4=0: can reach all cells with Chebyshev=1.
        // (1,1): Manhattan=2, Chebyshev=1. 2 <= 2+0=2 ✓, 1 <= 1+0=1 ✓. OK.
        // (0,0): distance 0. 0 <= 2 ✓, 0 <= 1 ✓. OK (it's the starting cell).
        // k8=0, k4=2: Manhattan expansion by 2. Reach: Manhattan <= 2.
        // (1,1): Manhattan=2, Chebyshev=1. 2 <= 0+2=2 ✓, 1 <= 0+2=2 ✓. But can we reach (1,1) with only 4 ops?
        // '4' expands orthogonally only. (0,0)→(1,0)→(1,1). Yes! ✓
        // k8=1, k4=0: (1,1): Chebyshev=1<=1, Manhattan=2<=2. ✓
        // (2,0): Chebyshev=2>1. Not reachable with just one '8'. ✓ (correct, can't reach)
        //
        // So the condition seems to be:
        //   max(|x|,|y|) <= k8 + k4
        //   AND |x|+|y| <= 2*k8 + k4
        
        int dx = abs(x), dy = abs(y);
        int maxd = max(dx, dy);
        int mand = dx + dy;
        bool reachable = (maxd <= cnt8 + cnt4) && (mand <= 2 * cnt8 + cnt4);
        cout << (reachable ? "1" : "0") << "\n";
    }
    return 0;
}
