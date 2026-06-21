#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<int> m(n), b(n);
        for (int i = 0; i < n; i++) cin >> m[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        vector<vector<long long>> dp(n+1, vector<long long>(k+1, 0));
        for (int day = 1; day <= k; day++) {
            vector<long long> ndp(n+1, 0);
            for (int tree = 0; tree < n; tree++) {
                long long best = 0;
                for (int prev = 0; prev < n; prev++) {
                    best = max(best, dp[prev][day-1] + (long long)b[prev] * (day-1) + m[tree]);
                }
                ndp[tree] = best;
            }
            for (int tree = 0; tree < n; tree++) dp[tree][day] = ndp[tree];
        }
        long long ans = 0;
        for (int tree = 0; tree < n; tree++)
            ans = max(ans, dp[tree][k] + (long long)b[tree] * (k-1));
        cout << ans << endl;
    }
    return 0;
}