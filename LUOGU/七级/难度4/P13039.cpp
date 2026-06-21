#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        string D;
        cin >> D;

        sort(D.begin(), D.end());

        long long ans = 1e18;

        do {
            int n = D.size();
            for (int mask = 1; mask < (1 << n); mask++) {
                if (__builtin_popcount(mask) == 0 || __builtin_popcount(mask) == n) continue;

                string s1, s2;
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) s1 += D[i];
                    else s2 += D[i];
                }

                if (s1[0] == '0' || s2[0] == '0') continue;

                long long v1 = stoll(s1);
                long long v2 = stoll(s2);
                ans = min(ans, abs(v1 - v2));
            }
        } while (next_permutation(D.begin(), D.end()));

        cout << "Case #" << t << ": " << ans << "\n";
    }

    return 0;
}
