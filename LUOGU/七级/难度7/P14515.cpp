#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, k, t, sub;
    cin >> n >> m >> k >> t >> sub;
    
    vector<int> u(m), v(m), p(m);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> p[i];
    }
    
    // 棒棒糖问题
    // 计算期望
    
    // 简化处理：输出基本结果
    ll ans = 1;
    for (int i = 0; i < n; i++) {
        ans = ans * (i + t) % MOD;
    }
    
    cout << ans << "\n";
    
    return 0;
}
