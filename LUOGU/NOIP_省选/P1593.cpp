#include <iostream>
#include <vector>
using namespace std;

const int MOD = 9901;

long long pow_mod(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

long long sum_geo(long long p, long long c) {
    // 1 + p + p^2 + ... + p^c
    if (c == 0) return 1;
    if (c % 2 == 0) {
        return (sum_geo(p, c/2 - 1) * (1 + pow_mod(p, c/2 + 1)) + pow_mod(p, c/2)) % MOD;
    } else {
        return sum_geo(p, c/2) * (1 + pow_mod(p, c/2 + 1)) % MOD;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long a, b;
    cin >> a >> b;
    
    if (a == 0) {
        cout << 0 << "\n";
        return 0;
    }
    
    long long ans = 1;
    for (long long p = 2; p * p <= a; p++) {
        if (a % p == 0) {
            long long c = 0;
            while (a % p == 0) {
                a /= p;
                c++;
            }
            ans = ans * sum_geo(p % MOD, c * b) % MOD;
        }
    }
    if (a > 1) {
        ans = ans * sum_geo(a % MOD, b) % MOD;
    }
    
    cout << ans << "\n";
    return 0;
}