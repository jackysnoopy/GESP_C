#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<long long> x(n), t(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        for (int i = 0; i < n; i++) cin >> t[i];
        // Binary search on x0 (optimal meeting point).
        // Minimize max(|x[i]-x0| + t[i]).
        // This is a classic minimax problem.
        // Binary search on the answer D.
        // Check if there exists x0 such that |x[i]-x0| + t[i] <= D for all i.
        // => x[i] - (D - t[i]) <= x0 <= x[i] + (D - t[i]).
        // Intersect all intervals.
        long long lo = 0, hi = 2e9;
        while (lo < hi) {
            long long D = (lo + hi) / 2;
            long long lox = -1e18, hix = 1e18;
            bool ok = true;
            for (int i = 0; i < n; i++) {
                if (D < t[i]) { ok = false; break; }
                long long range = D - t[i];
                lox = max(lox, x[i] - range);
                hix = min(hix, x[i] + range);
            }
            if (ok && lox <= hix) hi = D;
            else lo = D + 1;
        }
        long long D = lo;
        // Find x0
        long long lox = -1e18, hix = 1e18;
        for (int i = 0; i < n; i++) {
            long long range = D - t[i];
            lox = max(lox, x[i] - range);
            hix = min(hix, x[i] + range);
        }
        // x0 is any value in [lox, hix]. Output with 1 decimal if needed.
        if (lox == hix) {
            cout << lox << "\n";
        } else if ((lox + hix) % 2 == 0) {
            cout << (lox + hix) / 2 << "\n";
        } else {
            cout << fixed << setprecision(1) << (double)(lox + hix) / 2.0 << "\n";
        }
    }
    return 0;
}
