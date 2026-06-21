#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> L(n), R(n);
        for (int i = 0; i < n; ++i) cin >> L[i] >> R[i];
        long long ans = 0;
        for (int bit = 60; bit >= 0; --bit) {
            long long trybit = ans | (1LL << bit);
            bool ok = true;
            for (int i = 0; i < n; ++i) {
                long long mask = trybit;
                long long bad = 0;
                for (int b = 60; b >= 0; --b) {
                    if ((mask >> b) & 1) {
                        if (!((L[i] >> b) & 1)) bad |= (1LL << b);
                    } else {
                        if ((R[i] >> b) & 1) bad |= (1LL << b);
                    }
                }
                if (bad != 0) {
                    ok = false;
                    break;
                }
            }
            if (ok) ans = trybit;
        }
        cout << ans << '\n';
    }
    return 0;
}
