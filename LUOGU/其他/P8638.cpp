#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (len == 1) {
                dp[i][j] = 0;
                continue;
            }
            int best = dp[i + 1][j];
            best = min(best, dp[i][j - 1]);
            if (s[i] == s[j]) best = min(best, dp[i + 1][j - 1]);
            dp[i][j] = best;
        }
    }
    cout << dp[0][n - 1] << '\n';
    return 0;
}
