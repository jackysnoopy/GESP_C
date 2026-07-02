#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 250005;
int n;
long long p[MAXN];
long long dp[MAXN][3];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }
    
    // dp[i][0]: 第i个格子挖0层
    // dp[i][1]: 第i个格子挖1层
    // dp[i][2]: 第i个格子挖2层
    
    dp[1][0] = 0;
    dp[1][1] = p[1];
    dp[1][2] = 2 * p[1];
    
    for (int i = 2; i <= n; i++) {
        // 挖0层
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        
        // 挖1层
        dp[i][1] = max(dp[i-1][0], max(dp[i-1][1], dp[i-1][2])) + p[i];
        
        // 挖2层
        dp[i][2] = dp[i-1][2] + 2 * p[i];
    }
    
    long long ans = max(dp[n][0], max(dp[n][1], dp[n][2]));
    printf("%lld\n", ans);
    
    return 0;
}