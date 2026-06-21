#include <iostream>
#include <vector>
using namespace std;
long long phi(long long n) {
    long long res = n;
    for (long long p = 2; p * p <= n; ++p) {
        if (n % p == 0) {
            res = res / p * (p - 1);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) res = res / n * (n - 1);
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    long long n; cin >> n;
    long long ans = 0;
    for (long long d = 1; d * d <= n; ++d) {
        if (n % d == 0) {
            ans += d * phi(n / d);
            if (d != n / d) ans += (n / d) * phi(d);
        }
    }
    cout << ans << '\n';
    return 0;
}
