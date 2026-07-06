#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, a, b;
    cin >> n >> m >> a >> b;
    if (a > b) swap(a, b);

    auto check = [&](long long k) -> bool {
        if (a == b) {
            return k * a <= n && k * a <= m;
        }
        long long d = b - a;
        // 需要存在 x ∈ [0, k]，使得:
        // a*x + b*(k-x) <= n  →  (b-a)*x >= b*k - n
        // b*x + a*(k-x) <= m  →  (b-a)*x <= m - a*k
        long long x_low = 0;
        long long num = b * k - n;
        if (num > 0) {
            x_low = (num + d - 1) / d;  // ceil(num/d)
        }
        if (m < a * k) return false;
        long long x_high = min(k, (m - a * k) / d);  // floor
        return x_low <= x_high;
    };

    long long lo = 0, hi = (n + m) / a;  // 安全上界
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << endl;
    return 0;
}
