#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
int n, A, B;
long long Y[MAXN];
long long pre[MAXN];

int main() {
    scanf("%d%d%d", &n, &A, &B);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &Y[i]);
        pre[i] = pre[i - 1] + Y[i];
    }
    
    // 枚举每一位，从高位到低位
    long long ans = 0;
    for (int bit = 60; bit >= 0; bit--) {
        long long mask = ans | (1LL << bit);
        bool ok = false;
        
        // 检查是否能用不超过B组完成
        vector<int> dp(n + 1, n + 1);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                long long sum = pre[i] - pre[j];
                if ((sum & mask) == sum) {
                    dp[i] = min(dp[i], dp[j] + 1);
                }
            }
        }
        
        if (dp[n] <= B) {
            ans = mask;
        }
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
