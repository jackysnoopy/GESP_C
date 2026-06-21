#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, Sa, Sb, Sc, Sd, A1, Mod;
    cin >> n >> Sa >> Sb >> Sc >> Sd >> A1 >> Mod;
    auto F = [&](long long x) -> long long {
        return ((Sa * x % Mod * x % Mod * x % Mod) + (Sb * x % Mod * x % Mod) + (Sc * x % Mod) + Sd) % Mod;
    };
    vector<long long> a(n);
    a[0] = A1 % Mod;
    long long a0 = 0;
    for (int i = 1; i < n; i++) {
        a[i] = (F(a[i-1]) + F(a0)) % Mod;
        if (i >= 2) a0 = a[i-2];
    }
    // Find min max |a[i]-b[i]| such that b is non-decreasing
    // Binary search on answer
    long long lo = 0, hi = Mod;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        // Check if feasible: b[i] in [a[i]-mid, a[i]+mid] and b non-decreasing
        long long cur = 0; // current b value (minimum possible)
        bool ok = true;
        for (int i = 0; i < n; i++) {
            long long lo_i = a[i] - mid;
            long long hi_i = a[i] + mid;
            cur = max(cur, lo_i);
            if (cur > hi_i) { ok = false; break; }
        }
        if (ok) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
