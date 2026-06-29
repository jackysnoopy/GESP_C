#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, p, q, r;
    cin >> n >> p >> q >> r;
    
    // 咏叹调调律问题
    // 对于每个长度k，计算咏叹调的音韵之和
    
    // 动态规划
    // dp[i][a][b][c] = 长度为i，有a个A，b个B，c个C的咏叹调数量
    
    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1, 0));
    dp[0][0] = 1;
    
    for (int i = 1; i <= n; i++) {
        vector<vector<ll>> new_dp(n + 1, vector<ll>(n + 1, 0));
        
        for (int a = 0; a <= i; a++) {
            for (int b = 0; b <= i - a; b++) {
                int c = i - a - b;
                if (c < 0) continue;
                
                ll ways = 0;
                
                // 添加A
                if (a > 0) {
                    ways = (ways + dp[a - 1][b]) % MOD;
                }
                
                // 添加B
                if (b > 0) {
                    ways = (ways + dp[a][b - 1]) % MOD;
                }
                
                // 添加C
                if (c > 0) {
                    ways = (ways + dp[a][b]) % MOD;
                }
                
                new_dp[a][b] = ways;
            }
        }
        
        dp = new_dp;
    }
    
    // 计算答案
    ll ans = 0;
    for (int a = 0; a <= n; a++) {
        for (int b = 0; b <= n - a; b++) {
            int c = n - a - b;
            if (c < 0) continue;
            
            ll ways = dp[a][b];
            ll val = 1;
            for (int i = 0; i < a; i++) val = val * p % MOD;
            for (int i = 0; i < b; i++) val = val * q % MOD;
            for (int i = 0; i < c; i++) val = val * r % MOD;
            
            ans = (ans + ways * val) % MOD;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
