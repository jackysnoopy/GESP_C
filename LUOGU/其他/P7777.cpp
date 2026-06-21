#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long n, p, q;
        cin >> n >> p >> q;
        long long ans = 0;
        if (p <= q) {
            long long pairs = n / 2;
            ans = pairs * q;
            if (n % 2 == 1) ans += p;
        } else {
            for (int i = 1; i <= n; i++) {
                if (i % 2 == 0 && i < n) {
                    ans += q;
                    i++;
                } else {
                    ans += (long long)i * p;
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
