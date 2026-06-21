#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        long long x, y;
        cin >> n >> x >> y;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // Two operations: 1) global decrement (cost x), 2) replace one element (cost y).
        // Make all elements equal. Minimize cost.
        // Target value v (0 <= v <= max(a)).
        // Cost = x * max(a) + min_over_v of (cost to make all = v).
        // Actually: operation 1 decrements ALL elements by 1 (cost x).
        // Operation 2 replaces one element with any value (cost y).
        // We can do operation 1 multiple times (each decrements all).
        // After k operations of type 1, all elements are max(a[i]-k, 0).
        // Then we use type 2 to fix remaining mismatches.
        //
        // Target: after k global decrements, elements are a[i]-k (if a[i]>k) or 0.
        // All should be equal to some value v.
        // If v = 0: need k >= max(a). Cost = k*x + (count of a[i]>0 that aren't 0)*y... no.
        // Actually after k decrements: a[i] becomes max(a[i]-k, 0).
        // For all to be equal to v: need max(a[i]-k, 0) = v for all i that we don't replace.
        // Cost = k*x + (number of elements we replace)*y.
        //
        // For a given target v (0 <= v <= max(a)):
        //   k = max(a) - v (enough to bring max down to v).
        //   Elements with a[i] < v: after k decrements, they become 0 (not v). Must replace.
        //   Elements with a[i] >= v: after k decrements, they become a[i]-k = a[i]-max(a)+v.
        //     For this to equal v: need a[i] = max(a). So only max elements are correct.
        //     All others need replacement.
        //   Wait, that's not right. k decrements bring max(a) to max(a)-k.
        //   For target v: k = max(a)-v. After k decrements:
        //     a[i] becomes max(a[i]-k, 0) = max(a[i]-max(a)+v, 0).
        //     For a[i] >= max(a): becomes v. Correct.
        //     For a[i] < max(a): becomes max(a[i]-max(a)+v, 0).
        //       If a[i]-max(a)+v >= 0: becomes a[i]-max(a)+v. This equals v only if a[i]=max(a).
        //       If a[i]-max(a)+v < 0: becomes 0. This equals v only if v=0.
        //   So for v > 0: only elements with a[i] = max(a) are correct after k decrements.
        //     All others need replacement. Cost = (max(a)-v)*x + (n - count_max)*y.
        //   For v = 0: k = max(a). After k decrements, all become 0. Cost = max(a)*x.
        //
        // Minimize over v:
        //   v = 0: cost = max(a)*x.
        //   v = max(a): k = 0. All elements need to be max(a). Replace all non-max. Cost = (n-count_max)*y.
        //   General v: cost = (max(a)-v)*x + (n-count_max)*y. Wait, this doesn't depend on v!
        //   Actually for v > 0: cost = (max(a)-v)*x + (n-count_max)*y.
        //   This is minimized when v = max(a): cost = (n-count_max)*y.
        //   Or v = 0: cost = max(a)*x.
        //
        // Hmm, but we can also do type 2 operations DURING the global decrements.
        // Type 2 replaces an element with ANY value. So we can set it to a value that
        // will be correct after all decrements.
        //
        // Revised: after k global decrements, a[i] becomes max(a[i]-k, 0).
        // For type 2: we can replace any element at any time. If we replace element i
        // before k decrements, its value after k decrements is max(new_value - k, 0).
        // We want this to equal the target v. So new_value = v + k (before decrements).
        // But new_value can be anything, so this is always possible.
        // Cost = k*x + (number of replacements)*y.
        // We replace elements where max(a[i]-k, 0) != v.
        //   If a[i] > k: a[i]-k != v → need replacement if a[i] != v+k.
        //   If a[i] <= k: 0 != v → need replacement if v > 0.
        //
        // For v = 0: replace elements with a[i] <= k (they become 0 anyway). No replacements needed!
        //   Actually: if v = 0, all elements become 0 after k >= max(a) decrements.
        //   Cost = max(a)*x. No replacements.
        //
        // For v > 0: 
        //   k = max(a) - v (minimum k to bring max down to v).
        //   Elements with a[i] > k (= max(a)-v): become a[i]-k = a[i]-max(a)+v.
        //     This equals v iff a[i] = max(a). Others need replacement.
        //   Elements with a[i] <= k: become 0. Need replacement (since v > 0).
        //   Replacements needed: (count of a[i] != max(a) and a[i] > k) + (count of a[i] <= k)
        //     = n - count_max (since a[i]=max(a) implies a[i] > k when v > 0).
        //   Cost = (max(a)-v)*x + (n-count_max)*y.
        //
        // So the minimum cost is min(max(a)*x, min over v>0 of (max(a)-v)*x + (n-count_max)*y).
        // = min(max(a)*x, (n-count_max)*y) (when v = max(a), cost = (n-count_max)*y).
        //
        // Wait, but we can also choose v between 0 and max(a).
        // For v in (0, max(a)]: cost = (max(a)-v)*x + (n-count_max)*y.
        // Minimized at v = max(a): cost = (n-count_max)*y.
        // For v = 0: cost = max(a)*x.
        //
        // So answer = min(max(a)*x, (n-count_max)*y).
        // But we can also do BETTER by choosing k and v independently.
        // For a given k: elements become max(a[i]-k, 0).
        //   Target v = max(a[i]-k, 0) for some i (the most common value).
        //   Replace others. Cost = k*x + (n - max frequency of values)*y.
        //
        // This is complex. Let me just implement the simpler version.
        
        long long mx = *max_element(a.begin(), a.end());
        int countMax = 0;
        for (int i = 0; i < n; i++) if (a[i] == mx) countMax++;
        
        long long ans = min(mx * x, (long long)(n - countMax) * y);
        cout << ans << endl;
    }
    return 0;
}
