#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    // Remove max and min, maximize sum of remaining after at most m increments
    // Binary search on the minimum value we want all remaining to reach
    // After sorting: remove a[0] (min) and a[n-1] (max)
    // Remaining: a[1]..a[n-2]. We can increment any element.
    // We want to maximize the average (or sum) of the n-2 remaining.
    // Actually we can also change which is min/max by incrementing.
    // Strategy: increment the smallest elements to make them larger.
    // Binary search on target t: can we make all n-2 middle elements >= t with <=m ops?
    // Actually we want to maximize sum of n-2 elements after removing min and max.
    // Better: we can increment elements. After incrementing, the min and max of ALL n elements
    // get removed. So we want to make the n-2 "middle" elements as large as possible.
    // Binary search on answer: for target sum S, can we achieve it?
    // Simpler: binary search on the minimum value all n-2 middle elements should reach.
    long long lo = a[0], hi = a[n-1] + m;
    long long best = 0;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        // Can we make at least n-2 elements >= mid?
        // Count how many increments needed for a[0..n-1] to have at least n-2 elements >= mid
        // Elements already >= mid: no cost. Others need mid - a[i] each.
        long long cost = 0;
        int cnt = 0;
        // We want n-2 elements >= mid. Sort, take the top n-2.
        // Actually: increment any elements. We need at least n-2 to be >= mid.
        // Sort ascending. For a[i] < mid, need mid-a[i] increments.
        // We want to minimize: pick n-2 elements, maximize how many are already >= mid.
        // Equivalently: at most 2 elements can be < mid.
        // Cost = sum of max(0, mid-a[i]) for all but 2 elements (the 2 smallest that stay low).
        // But we also need to account for max element removal...
        // Actually simpler: we can increase any element. After ops, remove min and max.
        // The answer = sum of n-2 middle elements. 
        // We want to maximize: (sum of all n) - min - max after operations.
        // If we set all elements to mid: cost = sum(max(0, mid-a[i])).
        // Then min >= some value, max = max(original max, mid).
        // This is getting complex. Let me use a simpler approach.
        // Binary search on the final minimum value among the n-2 kept elements.
        cost = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < mid) cost += mid - a[i];
        }
        // After raising all to mid, we remove the 2 with least contribution
        // Actually we can choose which 2 to remove. We want to remove 2 smallest.
        // If all are >= mid, cost is valid. But we can remove 2 cheapest-to-raise.
        // Hmm, let me think differently.
        // We want: after ops, remove 1 min and 1 max from ALL n, sum of rest is max.
        // This equals: sum(all n) + total_increments - min_after - max_after
        // To maximize this, we want to maximize (total_increments - min_after - max_after)
        // Incrementing raises total. But min/max might also change.
        // If we increment the smallest to be equal to others, min goes up.
        // 
        // Simpler approach: try all possible "minimum value" for the n-2 kept elements.
        // For target minimum = t, we need at least n-2 elements to have value >= t.
        // The 2 that don't meet this are the ones we'll remove as min/max.
        // Actually we remove exactly 1 min and 1 max.
        // So we need at least n-2 elements >= t, and the 2 removed are the overall min and max.
        // If we raise elements to t, the min is min(t, min of 2 kept < t) and max is max of all.
        // 
        // Let me just use brute force: binary search on target, check feasibility.
        // For target score per element = t, we need sum of n-2 kept >= t*(n-2).
        // After ops: total sum = sum(a) + ops_used. Remove 1 min, 1 max.
        // To maximize: maximize (sum + ops - min - max).
        // Key insight: increment only the smallest elements (to make min larger).
        // Binary search doesn't easily work here. Let me just use a direct approach.
        // Sort. For each possible "remove index" for min (0..n-2) and max (1..n-1),
        // compute cost and result. O(n^2) is too slow for n=1e5.
        // 
        // Direct approach: we have m increments. Best to increment the smallest element.
        // After incrementing smallest, it might become larger. Repeat.
        // The optimal: increment a[0] as much as possible, then a[1], etc.
        // After all increments, remove min (which is a[0] after ops) and max (a[n-1] after ops).
        // 
        // Actually for this problem, optimal strategy:
        // Sort ascending. We can only increase elements.
        // Remove 1 min and 1 max. Remaining n-2 elements we want to maximize.
        // We should NOT increase the max (a[n-1]) since we'll remove it anyway.
        // We should increase elements that will be in the kept set.
        // The kept set is a[1..n-2] or includes a[0] if a[0] is raised enough.
        // 
        // Simpler: let's say we keep elements at indices {0,1,...,n-1} minus {min_idx, max_idx}.
        // We want to maximize sum(kept) = total_sum + m - a[min_idx] - a[max_idx] + adjustments.
        // The kept elements' sum = sum(all) + m - (cost to raise min) - cost to raise max beyond target.
        // 
        // This is getting too complex for binary search. Let me just do it directly:
        // Sort ascending. We remove 1 element as min and 1 as max.
        // For each pair (i,j) with i<j, cost = max(0, t-a[i]) + ... for elements that need raising.
        // 
        // OK let me just implement the simplest correct solution:
        // Sort ascending. Increment a[0] (smallest) m times. Then remove a[0] and a[n-1].
        long long total = 0;
        for (int i = 1; i < n - 1; i++) total += a[i];
        long long extra = min((long long)m, a[n-1] - a[1]);
        total += extra;
        // Actually this isn't right either.
        // Let me think about it properly.
        // n elements, m increments of +1 each. Remove 1 min, 1 max.
        // Keep n-2 elements. Maximize sum of kept.
        // = total_sum + m - min_after - max_after
        // We control increments. min_after >= a[0], max_after >= a[n-1].
        // If we only increment a[0]: min_after = a[0]+m, max_after = a[n-1] (unchanged).
        // Result = sum + m - (a[0]+m) - a[n-1] = sum - a[0] - a[n-1].
        // If we increment other elements: min stays a[0], max stays a[n-1].
        // Result = sum + m - a[0] - a[n-1].
        // So it's always sum + m - a[0] - a[n-1]?? No...
        // Wait: if we increment a[0] to be > a[n-1], then max_after = a[0]+m.
        // But that's wasteful. Better to not do that.
        // So: result = sum(a) + m - a[0] - a[n-1]. This is constant!
        // That can't be right. Oh wait, the problem says remove ONE highest and ONE lowest.
        // So: result = sum of n-2 middle = sum(a[1..n-2]) after ops.
        // If we increment a[0] (to make it larger), a[0] might move into the middle.
        // Then a[1] becomes the new min and gets removed. Net effect: a[0]+k replaces a[1].
        // So we gain (a[0]+k - a[1]) if a[0]+k > a[1], but we also spent k increments.
        // Actually the optimal is: 
        // Keep a[2..n-1] minus a[n-1] = a[2..n-2] plus either a[0]+m or a[1].
        // Whichever is larger of (a[0]+m, a[1]) stays, the other is removed as min.
        // Sum = a[2]+...+a[n-2] + max(a[0]+m, a[1])
        // = sum(a[2..n-2]) + max(a[0]+m, a[1])
        best = 0;
        long long midsum = 0;
        for (int i = 2; i < n-1; i++) midsum += a[i];
        long long option1 = midsum + a[0] + m; // raise a[0], a[1] becomes min removed
        long long option2 = midsum + max(a[0] + m, a[1]); 
        // Actually if we raise a[0] by m, the set becomes {a[0]+m, a[1], a[2], ..., a[n-1]}
        // Remove min = min(a[0]+m, a[1]) and max = a[n-1]
        // Sum of rest = total + m - min(a[0]+m, a[1]) - a[n-1]
        // = sum(a) + m - min(a[0]+m, a[1]) - a[n-1]
        long long total_a = 0;
        for (int i = 0; i < n; i++) total_a += a[i];
        long long res1 = total_a + m - min(a[0]+m, a[1]) - a[n-1];
        // What if we distribute m among multiple elements?
        // If we raise a[0] and a[1]: min becomes min(a[0]+k0, a[1]+k1, a[2]).
        // This doesn't help more than raising just a[0].
        // Unless raising a[1] makes a[2] the min... no, we remove min.
        // Raising elements that won't be removed is wasteful.
        // Only raising a[0] (to potentially move it out of min position) is useful.
        // If a[0]+m <= a[1]: min=a[0]+m, sum=total+m-(a[0]+m)-a[n-1]=total-a[0]-a[n-1]
        // If a[0]+m > a[1]: min=a[1], sum=total+m-a[1]-a[n-1]
        best = max(res1, total_a - a[0] - a[n-1]); // 0 increments case
        cout << best << "\n";
        lo = hi + 1; // just break
    }
    return 0;
}
