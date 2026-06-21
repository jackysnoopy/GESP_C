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
        for (long long x = 0; x <= k; x++) {
            if (a * x + b * (k - x) <= n && b * x + a * (k - x) <= m)
                return true;
        }
        return false;
    };
    long long lo = 0, hi = min((n + m) / (a + b) * 2, min(n / a + m / b, n / b + m / a)) + 10;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
