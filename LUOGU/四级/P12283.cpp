#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    long long ans = 0;
    
    // For each consecutive pair of original positions (a[i], a[i+1]),
    // we need to insert points between them.
    // We track the "previous difference" from before this gap.
    // prev_diff = a[1] - a[0] for the first gap.
    
    for (int i = 1; i < n; i++) {
        long long gap = a[i] - a[i - 1];
        long long prev_diff = (i >= 2) ? a[i - 1] - a[i - 2] : gap;
        
        // We need to insert points between a[i-1] and a[i] such that
        // the chain of differences satisfies d[j+1] <= 2*d[j].
        // Starting with "previous difference" = prev_diff,
        // we want to reach total distance = gap.
        // Each new difference can be at most 2 * previous.
        // We want to maximize each difference to minimize inserts.
        
        long long remaining = gap;
        long long cur_max_diff = prev_diff;
        int inserts = 0;
        
        while (remaining > 2 * cur_max_diff) {
            // We must insert a point; the new difference is 2*cur_max_diff
            cur_max_diff = 2 * cur_max_diff;
            remaining -= cur_max_diff;
            inserts++;
        }
        // Now remaining <= 2*cur_max_diff, so we can reach in one more step
        // Actually, remaining is the last gap. We need remaining > 0.
        // If remaining == 0, we're done (but gap > 0 so remaining > 0 unless we subtracted exactly).
        // After the loop, remaining <= 2*cur_max_diff. But we need remaining to be the
        // actual last difference. If remaining > 0, we need 1 more step (the final point = a[i]).
        // But wait, the last difference IS remaining and it must satisfy remaining <= 2*cur_max_diff.
        // This is automatically true after the while loop.
        // However, we need to count inserts correctly.
        // Each "step" in the while inserts a point. After the loop, we have one more step
        // that reaches a[i] directly.
        
        // Let me reconsider. We start at a[i-1] and need to reach a[i].
        // prev_diff is the difference between a[i-2] and a[i-1] (or gap for i=1).
        // The first difference after a[i-1] must be <= 2 * prev_diff.
        // To minimize inserts, we maximize each difference.
        
        // Reset and redo properly
        remaining = gap;
        cur_max_diff = prev_diff;
        inserts = 0;
        
        // The last inserted point or a[i-1] gives us a "current difference" to use
        // for the constraint. Let me think differently.
        // We need d1, d2, ..., d(k+1) where:
        //   d1 <= 2 * prev_diff
        //   d(j+1) <= 2 * d(j) for j >= 1
        //   d1 + d2 + ... + d(k+1) = gap
        //   k = number of inserted points
        // Minimize k = (number of differences) - 1.
        
        // To minimize k, we maximize each difference:
        //   d1 = min(gap, 2*prev_diff)
        //   d2 = min(gap - d1, 2*d1)
        //   etc.
        // Stop when the remaining distance can be covered in one step.
        
        long long used = 0;
        cur_max_diff = 2 * prev_diff;
        
        while (used + cur_max_diff < gap) {
            used += cur_max_diff;
            inserts++;
            cur_max_diff = 2 * cur_max_diff;
            if (cur_max_diff > gap) cur_max_diff = gap; // cap to avoid overflow
        }
        // After loop: used + cur_max_diff >= gap
        // So remaining = gap - used <= cur_max_diff
        // We need one more step (the final one reaching a[i]), but it doesn't need an insert
        // Wait, inserts counts intermediate points. If we have k+1 differences, we need k inserts.
        // used counts points we've "passed" via inserts. The last step reaches a[i] directly.
        // Actually: after the loop, we have used = sum of first `inserts` differences.
        // remaining = gap - used, and remaining <= cur_max_diff = 2^(inserts+1) * prev_diff
        // But we haven't added the final step to remaining.
        // The total number of differences = inserts + 1 (the final one).
        // Hmm wait, the loop counts: each iteration adds one insert and one difference.
        // After the loop, remaining <= cur_max_diff means the last difference covers it.
        // So total differences = inserts + 1, meaning inserts intermediate points.
        
        // But there's a subtle issue: if gap == 0, no inserts needed. But gap > 0 always.
        // Also if prev_diff is already >= gap, no inserts needed (one step suffices).
        // But what if prev_diff == 0? That shouldn't happen since positions are strictly increasing.
        
        // Wait, I need to reconsider. After the while loop:
        // used = d1 + d2 + ... + d(inserts) where each dj was maximized
        // remaining = gap - used <= cur_max_diff
        // We need one more difference: d(inserts+1) = remaining
        // This must satisfy d(inserts+1) <= 2 * d(inserts)
        // d(inserts) = cur_max_diff / 2 (the previous iteration's cur_max_diff)
        // Actually cur_max_diff = 2^(inserts+1) * prev_diff at this point
        // and the last chosen difference was cur_max_diff / 2 = 2^inserts * prev_diff
        // remaining <= cur_max_diff = 2 * (2^inserts * prev_diff) = 2 * d(inserts) ✓
        
        ans += inserts;
    }
    
    cout << ans << "\n";
    return 0;
}
