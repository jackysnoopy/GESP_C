#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        vector<int> cnt(n + 2, 0);
        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            cnt[l]++;
            cnt[r + 1]--;
        }
        // Compute prefix sum to get how many operations cover each position
        vector<long long> ops(n, 0);
        long long cur = 0;
        for (int i = 0; i < n; i++) {
            cur += cnt[i];
            ops[i] = cur;
        }
        // Each a[i] can change by [-ops[i], +ops[i]].
        // We want to minimize max(a[i]+delta[i]) - min(a[i]+delta[i]).
        // Binary search on answer D: can we achieve range <= D?
        // For each position i, the possible values are [a[i]-ops[i], a[i]+ops[i]].
        // We want to find values in these ranges such that max-min <= D.
        // This is feasible iff there exists some value v such that every range 
        // [a[i]-ops[i], a[i]+ops[i]] overlaps with [v, v+D].
        // Equivalently: max(a[i]-ops[i]) <= min(a[i]+ops[i]) + D.
        // The minimum D is max(0, max(a[i]-ops[i]) - min(a[i]+ops[i])).
        
        long long maxLo = -1e18, minHi = 1e18;
        for (int i = 0; i < n; i++) {
            long long lo = a[i] - ops[i];
            long long hi = a[i] + ops[i];
            maxLo = max(maxLo, lo);
            minHi = min(minHi, hi);
        }
        long long ans = max(0LL, maxLo - minHi);
        cout << ans << "\n";
    }
    return 0;
}
