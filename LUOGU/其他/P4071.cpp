#include <iostream>
#include <vector>
using namespace std;
const long long MOD = 1000000007;
long long power(long long b, long long e, long long m) {
    long long r = 1; b %= m;
    while (e > 0) { if (e & 1) r = r * b % m; b = b * b % m; e >>= 1; }
    return r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    int MAX = 1000000;
    vector<long long> fac(MAX + 1, 1), invf(MAX + 1, 1);
    for (int i = 1; i <= MAX; ++i) fac[i] = fac[i - 1] * i % MOD;
    invf[MAX] = power(fac[MAX], MOD - 2, MOD);
    for (int i = MAX - 1; i >= 0; --i) invf[i] = invf[i + 1] * (i + 1) % MOD;
    vector<long long> D(MAX + 1, 0);
    D[0] = 1; D[1] = 0;
    for (int i = 2; i <= MAX; ++i) D[i] = (i - 1) * (D[i - 1] + D[i - 2]) % MOD;
    while (T--) {
        int n, m; cin >> n >> m;
        long long c = fac[n] % MOD * invf[m] % MOD * invf[n - m] % MOD;
        cout << c * D[n - m] % MOD << '\n';
    }
    return 0;
}
