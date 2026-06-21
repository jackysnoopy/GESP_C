#include <iostream>
#include <cstring>
using namespace std;
long long dp[10001];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    memset(dp, 0, sizeof(dp));
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int j = 1; j < i; j++)
            dp[i] = max(dp[i], dp[j] * dp[i - j] + 1);
    cout << dp[n] << "\n";
    return 0;
}
