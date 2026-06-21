#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

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
    long long L;
    int cs = 0;
    while (cin >> L && L) {
        long long g = gcd(8LL, L);
        long long m = 9LL * L / g;
        if (gcd(10LL, m) != 1) {
            cout << "Case " << ++cs << ": 0" << endl;
            continue;
        }
        long long phi = m, tmp = m;
        for (long long p = 2; p * p <= tmp; ++p) {
            if (tmp % p == 0) {
                phi = phi / p * (p - 1);
                while (tmp % p == 0) tmp /= p;
            }
        }
        if (tmp > 1) phi = phi / tmp * (tmp - 1);
        long long ans = phi;
        vector<long long> divs;
        for (long long d = 1; d * d <= phi; ++d) {
            if (phi % d == 0) {
                divs.push_back(d);
                if (d * d != phi) divs.push_back(phi / d);
            }
        }
        sort(divs.begin(), divs.end());
        for (long long d : divs) {
            if (power(10, d, m) == 1) { ans = d; break; }
        }
        cout << "Case " << ++cs << ": " << ans << endl;
    }
    return 0;
}
