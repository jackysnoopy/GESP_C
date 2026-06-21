#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, X;
    cin >> n >> X;
    vector<int> x(n), a(n), b(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> a[i] >> b[i];
    // At each x, bird must be in (a, b) open interval
    // Bird position at x: y = 2*clicks - x (from (0,0), each click = +1, no click = -1)
    // So y + x must be even, and clicks = (y+x)/2
    // At position x_i, y must be in (a_i, b_i) and y has same parity as x_i
    // Feasibility: maintain [lo, hi] of possible y values at current x
    // At x, y must be in intersection with (a, b) and have correct parity
    long long lo = 0, hi = 0;
    int prevX = 0;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int dx = x[i] - prevX;
        lo -= dx; hi += dx; // expand range
        lo = max(lo, (long long)a[i]+1);
        hi = min(hi, (long long)b[i]-1);
        if (lo > hi) { cout << "NIE\n"; return 0; }
        // Adjust parity
        if ((lo & 1) != (x[i] & 1)) lo++;
        if ((hi & 1) != (x[i] & 1)) hi--;
        if (lo > hi) { cout << "NIE\n"; return 0; }
        prevX = x[i];
    }
    // At x=X, we just need to reach any y >= 0 with correct parity
    int dx = X - prevX;
    lo -= dx; hi += dx;
    if (lo < 0) lo = (0 & 1) == (X & 1) ? 0 : 1;
    cout << (lo + X) / 2 << "\n";
    return 0;
}
