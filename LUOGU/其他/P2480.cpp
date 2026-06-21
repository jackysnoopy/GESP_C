#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 999911659;
long long N, K;

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

long long comb_mod(long long n, long long k, long long p) {
    if (k > n) return 0;
    long long res = 1;
    for (long long i = 0; i < k; ++i) {
        res = res * (n - i) % p;
        res = res * power(i + 1, p - 2, p) % p;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> K;
    if (K == 0 || K == N) { cout << 1 << '\n'; return 0; }
    vector<long long> ps = {2, 3, 4679, 35617};
    vector<long long> rs;
    for (long long p : ps) {
        long long r = comb_mod(N % p, K % p, p);
        long long num = N / p, den = K / p;
        while (num > 0 || den > 0) {
            r = r * comb_mod(num % p, den % p, p) % p;
            num /= p; den /= p;
        }
        rs.push_back(r);
    }
    long long M = MOD - 1;
    long long ans = 0;
    for (int i = 0; i < 4; ++i) {
        long long Mi = M / ps[i];
        long long yi = power(Mi, ps[i] - 2, ps[i]);
        ans = (ans + rs[i] * Mi % M * yi % M) % M;
    }
    cout << power(N == K ? 1 : 0, ans, MOD) << '\n';
    return 0;
}
