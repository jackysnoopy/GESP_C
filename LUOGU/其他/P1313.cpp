#include <iostream>
using namespace std;

const int MOD = 10007;

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long a, b, k, n, m;
    cin >> a >> b >> k >> n >> m;
    long long comb = 1;
    for (long long i = 0; i < n; ++i)
        comb = comb * (k - i) % MOD * power(i + 1, MOD - 2, MOD) % MOD;
    long long ans = comb * power(a, n, MOD) % MOD * power(b, m, MOD) % MOD;
    cout << ans << '\n';
    return 0;
}
