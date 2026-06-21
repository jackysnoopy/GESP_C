#include <iostream>
#include <algorithm>
using namespace std;
int dp[200001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int v, w, s;
        cin >> v >> w >> s;
        if (s == 0) {
            // Complete knapsack
            for (int j = v; j <= m; j++)
                dp[j] = max(dp[j], dp[j-v]+w);
        } else if (s == 1) {
            // 0-1 knapsack
            for (int j = m; j >= v; j--)
                dp[j] = max(dp[j], dp[j-v]+w);
        } else {
            // Bounded knapsack
            int k = 1;
            while (k <= s) {
                for (int j = m; j >= k*v; j--)
                    dp[j] = max(dp[j], dp[j-k*v]+k*w);
                s -= k;
                k *= 2;
            }
            if (s > 0) {
                for (int j = m; j >= s*v; j--)
                    dp[j] = max(dp[j], dp[j-s*v]+s*w);
            }
        }
    }
    cout << dp[m] << "\n";
    return 0;
}
