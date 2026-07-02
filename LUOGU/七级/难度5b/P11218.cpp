#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, T;
    cin >> c >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        string row1, row2;
        cin >> row1 >> row2;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            a[i] = row1[i] - '0';
            b[i] = row2[i] - '0';
        }

        int ans = 0;

        if (m >= n) {
            int cnt[4] = {0};
            for (int i = 0; i < n; i++) {
                int t = a[i] * 2 + b[i];
                cnt[t]++;
            }
            ans = 2 * cnt[3] + cnt[1] + cnt[2] - 2 * cnt[0];
            if (ans < 0) ans = 0;
        } else {
            for (int mask = 0; mask < (1 << n); mask++) {
                int bits = 0;
                for (int i = 0; i < n; i++) if (mask >> i & 1) bits++;
                if (bits > m) continue;

                int total = 0;
                for (int i = 0; i < n; i++) {
                    int ta = a[i], tb = b[i];
                    if (mask >> i & 1) {
                        ta = b[i];
                        tb = a[i];
                    }
                    total += ta - tb;
                }
                if (total > ans) ans = total;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
