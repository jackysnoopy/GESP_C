#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    
    // 计算前缀和
    vector<long long> sumA(n + 1, 0), sumB(m + 1, 0);
    for (int i = 0; i < n; i++) sumA[i + 1] = sumA[i] + a[i];
    for (int i = 0; i < m; i++) sumB[i + 1] = sumB[i] + b[i];
    
    // dp[i][j] 表示将第一个数列的前i个数和第二个数列的前j个数清空的最小得分
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 1e18));
    dp[0][0] = 0;
    
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] == 1e18) continue;
            
            // 尝试删除k1个数从第一个数列，k2个数从第二个数列
            for (int k1 = 1; i + k1 <= n; k1++) {
                long long s1 = sumA[i + k1] - sumA[i];
                for (int k2 = 1; j + k2 <= m; k2++) {
                    long long s2 = sumB[j + k2] - sumB[j];
                    long long score = (s1 - k1) * (s2 - k2);
                    dp[i + k1][j + k2] = min(dp[i + k1][j + k2], dp[i][j] + score);
                }
            }
        }
    }
    
    cout << dp[n][m] << "\n";
    return 0;
}