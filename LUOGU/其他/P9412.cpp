#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, m;
    cin >> t >> m;
    vector<int> w(m), v(m);
    for (int i = 0; i < m; i++) cin >> w[i] >> v[i];
    // 0/1 knapsack
    vector<int> dp(t + 1, 0);
    for (int i = 0; i < m; i++) {
        for (int j = t; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    cout << dp[t] << "\n";
    return 0;
}
