#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m, x;
        cin >> n >> m >> x;
        vector<string> board(n);
        for (int i = 0; i < n; i++) cin >> board[i];
        
        const int NEG = -10000;
        // Use 2 rows for space optimization
        vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(x + 1, NEG)));
        
        char c = board[0][0];
        if (c == '1') dp[0][0][0] = 1;
        else if (c == '0') dp[0][0][0] = 0;
        else {
            dp[0][0][0] = 0;
            if (x >= 1) dp[0][0][1] = 1;
        }
        
        int cur = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) continue;
                char ch = board[i][j];
                int prev = 1 - cur;
                if (j == 0) {
                    // First column: only from above
                    for (int k = 0; k <= x; k++) {
                        dp[cur][0][k] = NEG;
                        int fromAbove = dp[prev][0][k];
                        if (ch == '1') {
                            if (fromAbove != NEG) dp[cur][0][k] = fromAbove + 1;
                        } else if (ch == '0') {
                            if (fromAbove != NEG) dp[cur][0][k] = fromAbove;
                        } else {
                            if (fromAbove != NEG) dp[cur][0][k] = fromAbove;
                            if (k > 0 && dp[prev][0][k-1] != NEG)
                                dp[cur][0][k] = max(dp[cur][0][k], dp[prev][0][k-1] + 1);
                        }
                    }
                } else {
                    for (int k = 0; k <= x; k++) {
                        dp[cur][j][k] = NEG;
                        int bestSame = NEG;
                        if (i > 0 && dp[prev][j][k] != NEG) bestSame = max(bestSame, dp[prev][j][k]);
                        if (dp[cur][j-1][k] != NEG) bestSame = max(bestSame, dp[cur][j-1][k]);
                        
                        if (ch == '1') {
                            if (bestSame != NEG) dp[cur][j][k] = bestSame + 1;
                        } else if (ch == '0') {
                            if (bestSame != NEG) dp[cur][j][k] = bestSame;
                        } else {
                            if (bestSame != NEG) dp[cur][j][k] = bestSame;
                            if (k > 0) {
                                int bestPrev = NEG;
                                if (i > 0 && dp[prev][j][k-1] != NEG) bestPrev = max(bestPrev, dp[prev][j][k-1]);
                                if (dp[cur][j-1][k-1] != NEG) bestPrev = max(bestPrev, dp[cur][j-1][k-1]);
                                if (bestPrev != NEG) dp[cur][j][k] = max(dp[cur][j][k], bestPrev + 1);
                            }
                        }
                    }
                }
            }
            if (i < n - 1) cur = 1 - cur;
        }
        
        int ans = 0;
        for (int k = 0; k <= x; k++) ans = max(ans, dp[cur][m-1][k]);
        cout << ans << "\n";
    }
    return 0;
}
