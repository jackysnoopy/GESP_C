#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1000005;
const int MAXX = 20;
int n, v, x;
int A[MAXX];
int C[MAXN][MAXX];
long long dp[1 << MAXX];

int main() {
    scanf("%d %d %d", &n, &v, &x);
    for (int i = 0; i < x; i++) scanf("%d", &A[i]);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < x; j++) {
            scanf("%d", &C[i][j]);
        }
    }
    
    // 状态压缩DP
    memset(dp, 0, sizeof(dp));
    
    for (int i = 0; i < n; i++) {
        // 计算当前采集点的总容量
        int total = 0;
        for (int j = 0; j < x; j++) total += C[i][j];
        
        // 从大状态向小状态更新
        for (int mask = (1 << x) - 1; mask >= 0; mask--) {
            if (dp[mask] < 0) continue;
            
            // 尝试采集当前点
            int new_mask = mask;
            int used = 0;
            for (int j = 0; j < x; j++) {
                if (mask & (1 << j)) {
                    used += C[i][j];
                }
            }
            
            if (used + total <= v) {
                new_mask = mask;
                for (int j = 0; j < x; j++) {
                    if (C[i][j] > 0) {
                        new_mask |= (1 << j);
                    }
                }
                long long gain = 0;
                for (int j = 0; j < x; j++) {
                    if (!(mask & (1 << j)) && C[i][j] > 0) {
                        gain += A[j];
                    }
                }
                dp[new_mask] = max(dp[new_mask], dp[mask] + gain);
            }
        }
    }
    
    long long ans = 0;
    for (int mask = 0; mask < (1 << x); mask++) {
        ans = max(ans, dp[mask]);
    }
    
    printf("%lld\n", ans);
    return 0;
}