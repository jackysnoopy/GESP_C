#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; long long k; cin >> n >> k;
        vector<long long> b(n);
        for (int i = 0; i < n; i++) { int a; cin >> a >> b[i]; }
        long long totalGroups = 0;
        for (int i = 0; i < n; i++) totalGroups += b[i] / 3;
        if (totalGroups < k) { cout << -1 << "\n"; continue; }
        // Binary search: minimum S soldiers to guarantee k groups
        // Worst case: adversary distributes to minimize groups
        // With S soldiers, adversary puts 2 in each profession first (no groups)
        // Then extras form groups
        long long lo = 3 * k, hi = 3 * k;
        // Upper bound: worst case is picking all soldiers
        hi = 0;
        for (int i = 0; i < n; i++) hi += b[i];
        // But we need at least 3k
        if (hi < 3 * k) { cout << -1 << "\n"; continue; }
        // Binary search
        long long ans = hi;
        while (lo <= hi) {
            long long mid = (lo + hi) / 2;
            // Worst case groups for mid soldiers
            // Adversary fills each profession with min(b[i], 2) first
            long long remaining = mid;
            vector<long long> used(n, 0);
            for (int i = 0; i < n && remaining > 0; i++) {
                long long take = min(b[i], min(2LL, remaining));
                used[i] = take;
                remaining -= take;
            }
            // Now remaining soldiers go to professions with b[i] >= 3
            // Adversary distributes to minimize groups
            // For each extra soldier in a profession, it may or may not form a group
            // Profession i has used[i] soldiers. Adding more:
            //   if used[i] == 0: 0 groups. Adding 3 more = 1 group.
            //   if used[i] == 1: 0 groups. Adding 2 more = 1 group.
            //   if used[i] == 2: 0 groups. Adding 1 more = 1 group.
            // So the adversary adds soldiers one at a time, choosing the profession
            // that loses the fewest groups.
            // A profession with used[i] = 2 needs only 1 more for a group.
            // A profession with used[i] = 0 needs 3 more for a group.
            // Adversary prefers to add to professions that need more for a group.
            // Strategy: add to professions with used[i] = 0 first (need 3 for 1 group),
            // then used[i] = 1 (need 2 for 1 group), then used[i] = 2 (need 1 for 1 group).
            
            // Count professions by used count
            vector<long long> cap(n, 0);
            for (int i = 0; i < n; i++) cap[i] = b[i] - used[i];
            
            // Adversary fills used=0 professions first (wastes 3 per group)
            // Then used=1 (wastes 2 per group)
            // Then used=2 (wastes 1 per group)
            long long groups = 0;
            // Phase 1: fill used=0 professions
            for (int i = 0; i < n && remaining > 0; i++) {
                if (used[i] != 0) continue;
                // This profession needs 3 soldiers for 1 group
                // Adversary puts min(cap[i], remaining) soldiers
                long long take = min(cap[i], remaining);
                groups += take / 3;
                remaining -= take;
            }
            // Phase 2: fill used=1 professions
            for (int i = 0; i < n && remaining > 0; i++) {
                if (used[i] != 1) continue;
                long long take = min(cap[i], remaining);
                long long cur = used[i] + take;
                long long g = cur / 3;
                groups += g - 0; // 0 groups from used=1 initially
                remaining -= take;
            }
            // Phase 3: fill used=2 professions
            for (int i = 0; i < n && remaining > 0; i++) {
                if (used[i] != 2) continue;
                long long take = min(cap[i], remaining);
                long long cur = used[i] + take;
                groups += cur / 3;
                remaining -= take;
            }
            if (groups >= k) { ans = mid; hi = mid - 1; }
            else lo = mid + 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
