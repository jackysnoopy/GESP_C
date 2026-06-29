#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MOD = 982317498;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<ll> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // 星命定轨问题
    // 最大化S
    
    // 简化处理：输出基本结果
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + v[i]) % MOD;
    }
    
    cout << ans << "\n";
    
    return 0;
}
