#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = 0;
        for (int bit = 29; bit >= 0; bit--) {
            long long candidate = ans | (1LL << bit);
            int count = 0;
            long long xor_sum = 0;

            for (int i = 0; i < n; i++) {
                xor_sum ^= a[i];
                if ((xor_sum & candidate) == candidate) {
                    count++;
                    xor_sum = 0;
                }
            }

            if (count >= m) {
                ans = candidate;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
