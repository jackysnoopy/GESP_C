#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P11323: 双倍经验 (Double Experience)
// Given n monsters with HP and exp. Choose some to kill normally, rest double.
// Limited potions. Maximize total exp.
// Without data file, implementing knapsack approach.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> hp(n), exp(n), cost(n);
    for (int i = 0; i < n; i++) cin >> hp[i] >> exp[i] >> cost[i];
    
    // 0/1 knapsack: capacity m, maximize exp
    vector<long long> dp(m + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int j = m; j >= cost[i]; j--) {
            dp[j] = max(dp[j], dp[j - cost[i]] + exp[i]);
        }
    }
    cout << dp[m] << "\n";
    return 0;
}
