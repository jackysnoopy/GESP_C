#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; long long T; cin >> n >> T;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Binary search on D (minimum max discomfort).
    // For each person i, valid x % T: [(A[i]%T - D + T)%T, (A[i]%T + D)%T] mod T.
    // This is 2D+1 consecutive residues mod T.
    // Intersection of all ranges must be non-empty.
    long long lo = 0, hi = 2e9;
    while (lo < hi) {
        long long D = (lo + hi) / 2;
        if (D >= T - 1) { hi = D; continue; }
        // Valid range for each person: [(A[i]%T - D + T)%T, (A[i]%T + D)%T] mod T
        // Represent as intervals mod T
        vector<pair<long long,long long>> intervals;
        intervals.push_back({0, T - 1});
        bool ok = true;
        for (int i = 0; i < n && ok; i++) {
            long long center = a[i] % T;
            long long l = (center - D % T + T) % T;
            long long r = (center + D) % T;
            vector<pair<long long,long long>> newIntervals;
            if (l <= r) {
                // Non-wrapping: [l, r]
                for (auto& inv : intervals) {
                    long long nl = max(inv.first, l);
                    long long nr = min(inv.second, r);
                    if (nl <= nr) newIntervals.push_back({nl, nr});
                }
            } else {
                // Wrapping: [l, T-1] ∪ [0, r]
                for (auto& inv : intervals) {
                    long long nl = max(inv.first, l);
                    long long nr = min(inv.second, T - 1);
                    if (nl <= nr) newIntervals.push_back({nl, nr});
                    nl = max(inv.first, (long long)0);
                    nr = min(inv.second, r);
                    if (nl <= nr) newIntervals.push_back({nl, nr});
                }
            }
            intervals = newIntervals;
            if (intervals.empty()) ok = false;
        }
        if (ok) hi = D;
        else lo = D + 1;
    }
    cout << lo << "\n";
    return 0;
}
