#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    string s;
    int caseNum = 1;
    while (cin >> s) {
        int n = s.size();
        int dp[1001][1001] = {};
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) dp[i][j] = dp[i + 1][j - 1] + 2;
                else dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        cout << "Case " << caseNum++ << ": " << dp[0][n - 1] << endl;
    }
    return 0;
}
