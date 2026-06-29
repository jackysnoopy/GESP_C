#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    sort(a.begin(), a.end());
    
    // 使用DP
    // dp[i]表示前i个数的最优差值
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1]; // 不选第i个
        
        // 选第i个和前面的一些
        for (int j = i - 1; j >= 0; j--) {
            if (a[j] < a[i]) {
                dp[i] = max(dp[i], a[j] + dp[j]);
            }
        }
    }
    
    printf("%d\n", dp[n]);
    
    return 0;
}
