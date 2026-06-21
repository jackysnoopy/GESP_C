#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a, b, c;
    cin >> n >> a >> b >> c;

    vector<int> dp(n + 1, 0);
    for (int i = 0; i <= c && i <= n; i++) {
        dp[i] = 1;
    }

    for (int i = c + 1; i <= n; i++) {
        long long ways = 0;
        if (i - a > 0) ways += dp[i - a];
        else ways += 1;
        if (i - b > 0) ways += dp[i - b];
        else ways += 1;
        dp[i] = ways % MOD;
    }

    cout << dp[n] << "\n";
    return 0;
}
