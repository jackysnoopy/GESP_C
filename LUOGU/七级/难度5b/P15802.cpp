#include <iostream>
using namespace std;

const long long MOD = 1000000000;

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (n <= 3) {
            cout << n << "\n";
            continue;
        }
        long long k = n / 3, r = n % 3;
        if (r == 1) { k--; r = 4; }
        else if (r == 0) r = 1;
        long long ans = qpow(3, k) * r % MOD;
        cout << ans << "\n";
    }
    return 0;
}
