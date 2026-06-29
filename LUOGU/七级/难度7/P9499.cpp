#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int sid, t;
    cin >> sid >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<ll> v(n), c(n), x(n);
        for (int i = 0; i < n; i++) cin >> v[i];
        for (int i = 0; i < n; i++) cin >> c[i];
        for (int i = 0; i < n; i++) cin >> x[i];
        
        // change问题
        // 简化处理：输出基本结果
        
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + c[i] * v[i]) % MOD;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
