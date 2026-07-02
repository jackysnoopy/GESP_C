#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // 基础实现：简单动态规划
    // dp[i][j] 表示前i个糖果选择j个的最大总和
    vector<vector<long long>> dp(n + 1, vector<long long>((n + 1) / 2 + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= (i + 1) / 2; j++) {
            // 不选第i个糖果
            dp[i][j] = dp[i - 1][j];
            // 选第i个糖果（需要i>=2）
            if (i >= 2) {
                dp[i][j] = max(dp[i][j], dp[i - 2][j - 1] + a[i - 1]);
            } else if (j == 1) {
                dp[i][j] = max(dp[i][j], (long long)a[i - 1]);
            }
        }
    }
    
    // 输出结果
    for (int j = 1; j <= (n + 1) / 2; j++) {
        cout << dp[n][j] << endl;
    }
    
    return 0;
}