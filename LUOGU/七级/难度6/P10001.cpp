#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    while (T--) {
        int n;
        long long m, c;
        cin >> n >> m >> c;
        
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        // 简单实现：贪心使用优惠券
        long long coins = 0;
        long long coupons = m;
        
        for (int i = 0; i < n; i++) {
            // 使用优惠券
            long long use = min(coupons, min(b[i], a[i]));
            coins += a[i] - use;
            coupons -= use;
            
            // 获得新优惠券
            coupons += (a[i] - use) / c;
        }
        
        cout << coins << "\n";
    }
    
    return 0;
}