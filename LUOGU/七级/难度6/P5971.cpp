#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = 1e9;
int dp[2][4][4];

int main() {
    int n;
    cin >> n;
    int type[1000001];
    for (int i = 1; i <= n; i++) {
        cin >> type[i];
    }

    // 特判：如果只有一个盘子且类型为1，则不需要移动
    if (n == 1 && type[1] == 1) {
        cout << 0 << endl;
        return 0;
    }

    for (int b = 0; b < 4; b++) {
        for (int c = 0; c < 4; c++) {
            dp[0][b][c] = INF;
        }
    }
    dp[0][0][0] = 0;
    int cur = 0;

    for (int i = 1; i <= n; i++) {
        int next = cur ^ 1;
        for (int b = 0; b < 4; b++) {
            for (int c = 0; c < 4; c++) {
                dp[next][b][c] = INF;
            }
        }

        int t = type[i];
        for (int b = 0; b < 4; b++) {
            for (int c = 0; c < 4; c++) {
                if (dp[cur][b][c] == INF) continue;
                int cost = dp[cur][b][c];

                // 移动到B柱
                if (b == 0) {
                    dp[next][t][c] = min(dp[next][t][c], cost + 1);
                } else {
                    // 需要先将B柱顶移动到C柱
                    dp[next][t][b] = min(dp[next][t][b], cost + 2);
                }

                // 移动到C柱
                if (c == 0) {
                    dp[next][b][t] = min(dp[next][b][t], cost + 1);
                } else {
                    // 需要先将C柱顶移动到B柱
                    dp[next][c][t] = min(dp[next][c][t], cost + 2);
                }
            }
        }
        cur = next;
    }

    int ans = INF;
    for (int b = 0; b < 4; b++) {
        for (int c = 0; c < 4; c++) {
            ans = min(ans, dp[cur][b][c]);
        }
    }
    cout << ans << endl;
    return 0;
}