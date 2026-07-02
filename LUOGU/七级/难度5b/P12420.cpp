#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long m, k;
        cin >> n >> m >> k;
        vector<long long> a(n);
        long long xorSum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            xorSum ^= a[i];
        }
        long long ans = xorSum;
        for (int bit = 30; bit >= 0; bit--) {
            long long mbit = (m >> bit) & 1;
            long long abit = (xorSum >> bit) & 1;
            if (abit == 0 && mbit == 1) {
                long long gain = 1LL << bit;
                long long cost = (k == 0) ? 0 : k;
                if (gain - cost > 0 || k == 0) {
                    ans = max(ans, xorSum + gain - (k == 0 ? 0 : k));
                }
            }
            if (abit == 1 && mbit == 0) {
                long long loss = 1LL << bit;
                long long val = xorSum - loss + (k == 0 ? 0 : k);
                ans = max(ans, val);
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
