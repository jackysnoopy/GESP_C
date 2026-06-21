#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m, k;
        cin >> n >> m >> k;
        int xorAll = 0, andAll = ~0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            xorAll ^= x;
            andAll &= x;
        }
        long long ans = 0;
        for (int b = 0; b < 31; b++) {
            int parity;
            if ((m >> b) & 1) {
                if ((andAll >> b) & 1) {
                    parity = n % 2;
                } else {
                    parity = 1;
                }
            } else {
                parity = (xorAll >> b) & 1;
            }
            if (parity) ans |= (1LL << b);
        }
        cout << ans << "\n";
    }
    return 0;
}
