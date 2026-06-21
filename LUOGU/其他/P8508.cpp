#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long x, p, q;
    if (!(cin >> n >> x >> p >> q)) return 0;
    vector<long long> t(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    auto can = [&](int d) -> bool {
        long long maxWork = x * d - (p * d + q - 1) / q;
        if (maxWork <= 0) return false;
        int used = 1;
        long long cur = 0;
        for (int i = 0; i < n; ++i) {
            if (t[i] > maxWork) return false;
            if (cur + t[i] > maxWork) {
                ++used;
                cur = t[i];
            } else {
                cur += t[i];
            }
        }
        return used <= d;
    };
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (can(mid)) hi = mid; else lo = mid + 1;
    }
    cout << lo << '\n';
    return 0;
}
