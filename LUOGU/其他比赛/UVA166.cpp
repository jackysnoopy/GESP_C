#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int coins[6] = {5, 10, 20, 50, 100, 200};
    int have[6];
    while (true) {
        int total = 0;
        for (int i = 0; i < 6; i++) {
            cin >> have[i];
            total += have[i];
        }
        if (total == 0) break;
        double target;
        cin >> target;
        int tgt = (int)(target * 100 + 0.5);
        // dp[i] = min coins to make value i (in cents)
        int dp[601];
        fill(dp, dp + 601, 1000);
        dp[0] = 0;
        // For each coin type, try using 0..have[i] of them
        for (int c = 0; c < 6; c++) {
            for (int cnt = 0; cnt < have[c]; cnt++) {
                for (int v = tgt; v >= coins[c]; v--) {
                    if (dp[v - coins[c]] + 1 < dp[v])
                        dp[v] = dp[v - coins[c]] + 1;
                }
            }
        }
        cout << dp[tgt] << endl;
    }
    return 0;
}
