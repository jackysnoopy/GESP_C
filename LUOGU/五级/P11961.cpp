#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long qpow(long long a, long long b, long long p) {
    long long res = 1 % p;
    while (b) {
        if (b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

vector<long long> get_factors(long long n) {
    vector<long long> res;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long a, p;
        cin >> a >> p;
        if (qpow(a, p - 1, p) != 1) { cout << "No\n"; continue; }
        auto factors = get_factors(p - 1);
        bool ok = true;
        for (auto q : factors) {
            if (qpow(a, (p - 1) / q, p) == 1) { ok = false; break; }
        }
        cout << (ok ? "Yes" : "No") << "\n";
    }
    return 0;
}
