#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long S;
    cin >> n >> S;
    vector<long long> p(n), c(n);
    for (int i = 0; i < n; i++) cin >> p[i] >> c[i];
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) hi = max(hi, c[i]);
    hi = max(hi, 2000000LL);
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        long long cost = mid * S;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            long long remaining = c[i] - mid;
            if (remaining < 0) remaining = 0;
            cost += remaining * p[i];
            if (cost > 10000000000LL) { ok = false; break; }
        }
        if (ok && cost <= 10000000000LL) hi = mid;
        else lo = mid + 1;
    }
    long long ans = lo * S;
    for (int i = 0; i < n; i++) {
        long long remaining = c[i] - lo;
        if (remaining < 0) remaining = 0;
        ans += remaining * p[i];
    }
    cout << ans << "\n";
    return 0;
}
