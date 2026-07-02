#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int sid, t;
    cin >> sid >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<long long> v(n), c(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        
        vector<long long> x(n - 1);
        for (int i = 0; i < n - 1; i++) cin >> x[i];
        
        // 简单实现：计算初始总价值
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + c[i] % MOD * (v[i] % MOD)) % MOD;
        }
        
        // 这里需要更复杂的动态规划
        cout << ans << "\n";
    }
    
    return 0;
}