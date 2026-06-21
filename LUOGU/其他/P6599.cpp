#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n, l;
        cin >> n >> l;
        long long ans = 0;
        long long mod = 1000000007;
        for (int bit = 0; bit < 50; bit++) {
            long long mask = 1LL << bit;
            if (mask > n) break;
            long long fullPairs = min(n + 1, mask * 2);
            long long ones = min(n + 1 - mask, mask);
            ones = max(ones, 0LL);
            long long contribution = ones * (fullPairs - ones);
            contribution %= mod;
            contribution = contribution * (l % mod) % mod;
            contribution = contribution * ((l - 1) / 2 % mod) % mod;
            if (l % 2 == 0) {
                contribution += ones * ((l / 2) % mod) % mod;
            }
            ans = (ans + contribution) % mod;
        }
        cout << ans << "\n";
    }
    return 0;
}
