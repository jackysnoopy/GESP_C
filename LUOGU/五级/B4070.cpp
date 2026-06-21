#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    long long ans = 0;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; e++; }
            int k = (int)((sqrt(8LL * e + 1) - 1) / 2);
            ans += k;
        }
    }
    if (n > 1) ans += 1;
    cout << ans << "\n";
    return 0;
}
