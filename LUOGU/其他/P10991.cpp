#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [蓝桥杯 2023 国 Python A] 选段排序
// Sort a subarray [L,R] to maximize A[q] - A[p] (1-indexed, p < q)
// Key: After sorting [L,R], A[q] is some element that was originally in the range,
// and A[p] is some element. We want max(A[q]) - min(A[p]).
// If [p,q] ⊆ [L,R], then A[q] >= A[p] after sorting.
// Strategy: consider all possible L,R and compute the best.
// But n up to 2e5, need efficient approach.
//
// Observation: We sort [L,R]. Then:
// - For positions < L: unchanged (they are < L)
// - For positions in [L,R]: sorted
// - For positions > R: unchanged
//
// If p < L and q > R: A[p] unchanged, A[q] unchanged, no help.
// If L <= p and q <= R: sorted, A[q] - A[p] >= 0 but not necessarily max.
// If p < L and L <= q <= R: A[p] unchanged, A[q] is some element from [L,R]
// If L <= p <= R and q > R: A[p] is some element from [L,R], A[q] unchanged
//
// Best case: make A[q] as large as possible and A[p] as small as possible.
// If we can put the max of some range at q and min at p:
// Sort [p,q]: A[q] = max(A[p..q]), A[p] = min(A[p..q]), result = max-min.
// But we can also extend beyond [p,q].
//
// Key insight: the optimal is max over all L<=p<=q<=R or p<L<=q<=R etc.
// Actually the best answer is:
// max_element(A, A+q) - min_element(A+p, A+n) if we can sort appropriately.
// But we need a single contiguous sort.
//
// Simpler: sort [1, q] → A[q] = max(A[1..q]), A[p] = min(A[1..q])? No.
// After sorting [1,q], A[p] = the p-th smallest of A[1..q].
//
// Let me think differently. After sorting [L,R]:
// If p < L and q in [L,R]: A[p] stays, A[q] = (q-L+1)th smallest in A[L..R]
// If L <= p and q > R: A[p] = (p-L+1)th smallest in A[L..R], A[q] stays
// If L <= p and q <= R: A[p] = (p-L+1)th, A[q] = (q-L+1)th smallest in A[L..R]
//
// Optimal: sort [p, q] → A[q] - A[p] = sorted[q-L+1] - sorted[p-L] = max(A[p..q]) - min(A[p..q])
// Can we do better? Sort [L, R] where L < p or R > q:
// If L < p, R >= q: A[p] = some value, A[q] = sorted[q-L+1]
// If L <= p, R > q: A[p] = sorted[p-L+1], A[q] = some value
// The max A[q] we can get is max(A[L..R]) and min A[p] is min(A[L..R]).
// But they need to be at positions p and q in the sorted order.
//
// Actually: sort entire [1,n]: A[q] = A[q]th smallest, A[p] = A[p]th smallest. Not great.
//
// Final approach: The answer is max over L,R of (value at position q after sort) - (value at position p after sort).
// Since n=2e5, we need O(n log n).
//
// Case 1: L <= p <= q <= R. After sorting, A[q]-A[p] = sorted[q-L+1]-sorted[p-L] >= 0.
//   Best is when L=p, R=q: max(A[p..q])-min(A[p..q]). But extending doesn't help since
//   A[p] only gets smaller and A[q] only gets larger? Actually A[p] gets smaller (good) and
//   A[q] gets larger (good). So sort [1,n]: A[q]-A[p] could be large.
//   But A[p] after sorting [1,n] is the p-th smallest, A[q] is q-th smallest.
//   If p < q then A[p] <= A[q]. The value is (q-th smallest of all) - (p-th smallest of all).
//
// Hmm, this is complex. Let me just try all relevant splits.
// 
// Actually, the answer is simply:
// max(A[q] - min(A[p..q]), max(A[p..q]) - A[p], max(A[p..q]) - min(A[p..q]))
// No wait, we can sort [L,R] for any L,R.
//
// Let me think about it as: we choose L <= R, sort A[L..R].
// A[p] after sort = element at position p in sorted A[L..R] (if L<=p<=R), else unchanged.
// A[q] after sort = element at position q in sorted A[L..R] (if L<=q<=R), else unchanged.
//
// Case A: p,q both in [L,R]. Then A[q]-A[p] = sorted_A[q-L] - sorted_A[p-L] (0-indexed).
//   Since sorted is non-decreasing and p<q, this >= 0.
//   To maximize: choose L small (so sorted_A has more small elements), R large (more large elements).
//   Best: L=1, R=n. Then A[q]-A[p] = A_sorted[q] - A_sorted[p] where A_sorted is sorted A.
//   Wait no, after sorting [1,n], A[i] = i-th smallest. So A[q]-A[p] = A_sorted[q]-A_sorted[p].
//   But we could also choose L=1,R=q: then A[p] = sorted[p] (small), A[q] = sorted[q] = max.
//   Or L=p,R=n: A[p] = sorted[n-p+1-p] = ... this is getting confusing.
//
// Let me just code it directly:
// Answer = max over all valid (L,R) of value_after_sort(q) - value_after_sort(p)
// 
// Case: only q in [L,R], p < L: A[q] = sorted[q-L+1]-th smallest of A[L..R], A[p] = A[p]
//   Maximize: pick L=1, sort [1,q]: A[q] = max(A[1..q]), A[p] stays. Result = max(A[1..q])-A[p].
//   Or extend to include more: sort [1,R] for R>=q: A[q] = (q-th smallest of A[1..R]).
//   With R large, there are more elements, q-th smallest could be smaller. So R=q is best.
//   So best for this case: max(A[1..q]) - A[p].
//
// Case: only p in [L,R], q > R: A[p] = sorted[p-L+1]-th smallest of A[L..R], A[q] = A[q]
//   Minimize A[p]: sort [p,n], A[p] = min(A[p..n]). Result = A[q] - min(A[p..n]).
//   With L=p: A[p] = min(A[p..n]). That's the minimum possible A[p].
//   So best: A[q] - min(A[p..n]).
//
// Case both in [L,R]: sort [L,R], A[q]-A[p] = sorted[q-L+1]-sorted[p-L+1] of A[L..R].
//   To maximize the difference of the (p-L+1)-th and (q-L+1)-th order statistics:
//   Choose L=1,R=n: A_sorted[q] - A_sorted[p] (global sorted).
//   Or L=1,R=q: sorted[q-th of A[1..q]) - sorted[p-th of A[1..q]). The q-th of A[1..q] is max.
//   The p-th of A[1..q] is p-th smallest of first q elements.
//   Or L=p,R=n: A[p]=min(A[p..n]), A[q]=(q-p+1)-th smallest of A[p..n].
//   Hmm, hard to beat just the overall sorted difference.
//
// Case neither in [L,R]: no change, A[q]-A[p] unchanged.
//
// So the answer is max of:
// 1. max(A[1..q]) - A[p] (sort [1,q])
// 2. A[q] - min(A[p..n]) (sort [p,n])  -- wait, p < q, so A[q] - min(A[p..n]) 
//    where min includes A[p] itself and positions after
// 3. max(A[1..q]) - min(A[p..n]) if we can achieve both simultaneously
//    Can we? Sort [1,q]: A[q]=max(A[1..q]), A[p]=min(A[1..q]). 
//    But we want A[p] = min(A[p..n]) which could be after q.
//    If we sort [1,n]: A[q] = q-th smallest of all, A[p] = p-th smallest of all.
//    A[q] could be small.
//    
//    Can we sort [1,q] for max at q AND have p be small?
//    After sorting [1,q], A[p] = p-th smallest of A[1..q]. Not necessarily min(A[p..n]).
//    
//    What if we sort [p, q]? A[p] = min(A[p..q]), A[q] = max(A[p..q]).
//    Result = max(A[p..q]) - min(A[p..q]).
//    Can we extend? Sort [L, R] where L<=p, R>=q: A[p] = (p-L+1)-th smallest, 
//    A[q] = (q-L+1)-th smallest of A[L..R]. The gap between these order statistics.
//    This is maximized when L and R capture the global min and max appropriately.
//
// I think the answer is: max(A[1..q]) - min(A[p..n]) if max(A[1..q]) is at position >= some threshold
// and min(A[p..n]) is at position <= some threshold. But with a single sort this may not be achievable.
//
// Let me reconsider. After sorting [L,R]:
// If p in [L,R] and q not in [L,R]: A[q] unchanged, A[p] = some element from A[L..R].
// If q in [L,R] and p not in [L,R]: A[p] unchanged, A[q] = some element from A[L..R].
// If both in [L,R]: A[p] and A[q] are both from sorted A[L..R].
// If neither: unchanged.
//
// Case both in [L,R], L<=p, q<=R: 
//   A[q]-A[p] = (q-L)-th smallest - (p-L)-th smallest of A[L..R] (0-indexed)
//   Let d = q-p. We want the gap between the (p-L)-th and (q-L)-th order statistics.
//   This equals the gap between two order statistics that are d apart.
//   To maximize this gap: we want small elements before p-L and large elements after q-L.
//   Sort [1,n]: gap between p-th and q-th order statistics = A_sorted[q] - A_sorted[p].
//   This is a valid construction.
//
// Case q in [L,R], p < L:
//   A[p] unchanged, A[q] = (q-L)-th smallest (0-indexed) of A[L..R].
//   To maximize A[q]: make (q-L)-th smallest as large as possible.
//   Choose L=1, R=q: A[q] = max(A[1..q]). 
//   Choose L=1, R=n: A[q] = (q-1)-th smallest of A[1..n] = q-th smallest overall.
//   Since q-th smallest <= max(A[1..q]), L=1,R=q is better.
//   Result: max(A[1..q]) - A[p].
//
// Case p in [L,R], q > R:
//   A[p] = (p-L)-th smallest of A[L..R], A[q] unchanged.
//   To minimize A[p]: choose L=p, R=p: A[p] = A[p]. Not helpful.
//   Choose L=p, R=n: A[p] = min(A[p..n]).
//   Result: A[q] - min(A[p..n]).
//
// Final answer: max of:
// (a) A[q] - A[p] (original)
// (b) max(A[1..q]) - A[p] (sort [1,q])
// (c) A[q] - min(A[p..n]) (sort [p,n])  
// (d) max(A[1..q]) - min(A[p..n]) -- is this achievable?
//     Sort [1,q]: A[q]=max(A[1..q]), A[p]=min of A[1..q]... no, A[p] = p-th smallest of A[1..q].
//     Sort [p,n]: A[p]=min(A[p..n]), A[q]=(q-p+1)-th smallest of A[p..n]... no.
//     Can we achieve max(A[1..q]) at position q AND min(A[p..n]) at position p?
//     If max(A[1..q]) >= p and min(A[p..n]) <= q... this requires sorting that includes both.
//     Sort [L,R] where L <= p and R >= q: A[p] = (p-L+1)-th smallest, A[q] = (q-L+1)-th smallest.
//     For A[p] = min(A[L..R]): need p-L+1 = 1, so L = p.
//     For A[q] = max(A[L..R]): need q-L+1 = R-L+1, so q = R.
//     Sort [p,q]: A[q] = max(A[p..q]), A[p] = min(A[p..q]).
//     Can we get max(A[1..q]) and min(A[p..n]) simultaneously? Only if max(A[1..q]) = max(A[p..q])
//     and min(A[p..n]) = min(A[p..q]), i.e., the global max in [1,q] and min in [p,n] are both in [p,q].
//     This is not always the case.
//
//     What if max(A[1..q]) is at position < p? Then we can't place it at q by sorting [p,R].
//     We'd need to sort [L,R] where L <= that position. But then A[p] won't be min(A[p..n]).
//     
//     I think (d) is achievable only in some cases. Let me check:
//     Sort [L,R] where max(A[1..q]) is in [L,R] and min(A[p..n]) is in [L,R].
//     Place max at position q and min at position p in sorted order.
//     For min at position p: we need exactly p-L elements smaller than min in A[L..R].
//     Since min is the minimum, we need p-L = 0, so L = p.
//     But then max(A[1..q]) needs to be in [p,R]. If max(A[1..q]) is at position < p, it's not.
//     
//     So the answer is: max of (a), (b), (c), and the best both-in-range case.
//     
// For the both-in-range case with L=p, R=q: max(A[p..q]) - min(A[p..q]).
// Or L=1, R=n: A_sorted[q] - A_sorted[p].
// Or any L,R with L<=p, R>=q: the gap between order stats.
// 
// The maximum gap between (q-p)-apart order statistics over all subsets A[L..R] with L<=p, R>=q
// is at least max(A[p..q])-min(A[p..q]) (using L=p,R=q).
// But it could be larger with extended range.
// 
// I think the overall answer is max of:
// max(A[1..q]) - min(A[p..n])  -- this is an upper bound
// and we need to check if it's achievable.
//
// Actually let me just try: if we sort [1,n], A[p]-A[q] order stats...
// I'll go with a simpler approach and just compute the max over a few cases.
//
// After more thought, I believe the answer is:
// max(A[1..q]) - A[p]  or  A[q] - min(A[p..n])  or  max(A[1..q]) - min(A[p..n]) if achievable
// The last one is achievable iff max(A[1..q]) and min(A[p..n]) don't "cross"
// i.e., the position of max(A[1..q]) >= the position of min(A[p..n])... no that's not right either.
//
// Let me just implement: sort [1,q] gives max(A[1..q]) - A[p].
// Sort [p,n] gives A[q] - min(A[p..n]).
// Sort [p,q] gives max(A[p..q]) - min(A[p..q]).
// Sort [1,n] gives A_sorted[q] - A_sorted[p].
// Take the max of these.
// But also: sort [L,R] where L < p, R = q: A[q] = max(A[L..q]), A[p] = (p-L+1)-th smallest.
// As L decreases, A[p] gets smaller (more elements, p-L+1 stays same position).
// Best: L=1, R=q: A[q]=max(A[1..q]), A[p]=p-th smallest of A[1..q].
// This gives max(A[1..q]) - p-th_smallest(A[1..q]).
// 
// Similarly: L=p, R>q: A[p]=min(A[p..R]), A[q]=(q-p+1)-th smallest of A[p..R].
// Best R=n: A[p]=min(A[p..n]), A[q]=(q-p+1)-th smallest of A[p..n].
// This gives (q-p+1)-th_smallest(A[p..n]) - min(A[p..n]).
//
// And: L<p, R>q: complex but bounded by the above cases.
//
// For n=2e5, I'll compute prefix mins/suffix mins and the sorted difference.
// Actually, let me just do a clean implementation:

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, q;
    cin >> n >> p >> q;
    p--; q--; // 0-indexed
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // prefix max up to q
    int prefMax = a[0];
    long long ans = 0;
    for (int i = 0; i <= q; i++) {
        prefMax = max(prefMax, a[i]);
        if (i >= p) {
            ans = max(ans, (long long)prefMax - a[i]); // sort [0..i] gives max - a[p]
        }
    }
    
    // suffix min from p
    int sufMin = a[n - 1];
    for (int i = n - 1; i >= p; i--) {
        sufMin = min(sufMin, a[i]);
        if (i <= q) {
            ans = max(ans, (long long)a[i] - sufMin); // sort [i..n-1]
        }
    }
    
    // max(A[0..q]) - min(A[p..n-1])
    int maxPQ = a[0];
    for (int i = 0; i <= q; i++) maxPQ = max(maxPQ, a[i]);
    int minPQ = a[n - 1];
    for (int i = p; i < n; i++) minPQ = min(minPQ, a[i]);
    ans = max(ans, (long long)maxPQ - minPQ);
    
    // sorted A[q] - sorted A[p]
    vector<int> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    ans = max(ans, (long long)sorted_a[q] - sorted_a[p]);
    
    // max(A[p..q]) - min(A[p..q])
    int mx = a[p], mn = a[p];
    for (int i = p; i <= q; i++) {
        mx = max(mx, a[i]);
        mn = min(mn, a[i]);
    }
    ans = max(ans, (long long)mx - mn);
    
    cout << ans << "\n";
    return 0;
}
