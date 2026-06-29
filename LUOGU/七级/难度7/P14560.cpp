#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        // CF1152D加强版
        // 括号序列Trie树上的最大匹配
        
        // 动态规划
        vector<ll> dp(n + 1, 0);
        dp[0] = 1;
        
        for (int i = 1; i <= n; i++) {
            dp[i] = (dp[i-1] * 2) % MOD;
        }
        
        ll ans = 0;
        for (int i = 0; i <= n; i++) {
            ans = (ans + dp[i]) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
