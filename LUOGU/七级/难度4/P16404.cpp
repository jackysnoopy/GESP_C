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
        long long x;
        int a1, a2, a3, a4;
        cin >> x >> a1 >> a2 >> a3 >> a4;

        long long best = x;

        for (int mask = 0; mask < (1 << 4); mask++) {
            int cnt[4] = {0};
            for (int i = 0; i < 4; i++) {
                if (mask & (1 << i)) cnt[i]++;
            }

            long long val = x;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < cnt[i]; j++) {
                    if (i == 0) val = (long long)(10 * sqrt(val));
                    else if (i == 1) val = (long long)(0.7 * val + 30);
                    else if (i == 2) val = (long long)(1.2 * val);
                    else val = val + 5;
                }
            }

            best = max(best, val);
        }

        cout << best << "\n";
    }

    return 0;
}
