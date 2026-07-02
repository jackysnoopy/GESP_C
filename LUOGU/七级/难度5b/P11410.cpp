#include <iostream>
#include <string>
using namespace std;

const long long MOD = 1e9 + 7;
const long long INV6 = 166666668;
const long long INV2 = 500000004;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

long long solve(long long n, long long d) {
    long long nd = n - d;
    long long t1 = (power(4, nd, MOD) - 1 + MOD) % MOD;
    long long t2 = (power(2, d + 2, MOD) - 1 + MOD) % MOD;
    long long t3 = (power(2, nd, MOD) - 1 + MOD) % MOD;
    long long ans = t1 * t2 % MOD * INV6 % MOD;
    ans = (ans - t3 * INV2 % MOD + MOD) % MOD;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    int q;
    cin >> n >> q;
    while (q--) {
        int k;
        string s;
        cin >> k >> s;
        long long d = k - 1;
        cout << solve(n, d) << "\n";
    }
    return 0;
}
