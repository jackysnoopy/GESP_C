#include <iostream>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    vector<int> primes;
    for (int i = 2; i <= 100000; i++) {
        bool ok = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) { ok = false; break; }
        }
        if (ok) primes.push_back(i);
    }
    while (t--) {
        int h;
        cin >> h;
        vector<int> dp(h + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= h; i++) {
            int p2 = 1;
            for (int k = 1; p2 <= i; k++) {
                if (dp[i - p2] != INT_MAX)
                    dp[i] = min(dp[i], dp[i - p2] + k);
                p2 *= 2;
            }
        }
        int ans = dp[h];
        for (int p : primes) {
            if (p > h) break;
            if (dp[h - p] != INT_MAX)
                ans = min(ans, dp[h - p] + 1);
        }
        cout << (ans == INT_MAX ? -1 : ans) << "\n";
    }
    return 0;
}
