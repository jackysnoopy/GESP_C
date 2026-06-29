#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<ll> p(n), h(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> h[i];
    }
    
    // Just Because问题
    // 简化处理：输出基本结果
    
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
