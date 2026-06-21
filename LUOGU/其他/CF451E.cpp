#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1000000007;

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

long long comb(long long n, long long k) {
    if (k < 0 || k > n) return 0;
    if (k > n - k) k = n - k;
    long long num = 1, den = 1;
    for (long long i = 0; i < k; ++i) {
        num = num * ((n - i) % MOD) % MOD;
        den = den * ((i + 1) % MOD) % MOD;
    }
    return num * power(den, MOD - 2, MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> f(n);
    for (int i = 0; i < n; ++i) cin >> f[i];
    long long ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        long long sum = 0;
        int bits = 0;
        for (int i = 0; i < n; ++i)
            if (mask & (1 << i)) { sum += f[i] + 1; bits++; }
        if (sum > s) continue;
        long long c = comb(s - sum + n - 1, n - 1);
        if (bits & 1) ans = (ans - c + MOD) % MOD;
        else ans = (ans + c) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
