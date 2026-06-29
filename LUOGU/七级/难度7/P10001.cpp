#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int n;
        ll m, c;
        cin >> n >> m >> c;
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        // 优惠购物：依次购买n个物品，初始m张优惠券
        // 每个物品价格a_i，优惠券上限b_i
        // 使用x张券(0<=x<=b_i)，付a_i-x金币，得floor((a_i-x)/c)张券
        // 贪心：每次使用尽量多的券来最小化金币花费
        // 但也要考虑未来需要券的情况
        
        // 简单贪心：如果c足够大，券的回收不重要，尽量用券
        // 如果c较小，需要保留一些券
        
        // 对于每个物品，使用min(b_i, current_coupons)张券
        // 然后获得floor((a_i-x)/c)张新券
        
        ll coupons = m;
        ll total_gold = 0;
        
        for (int i = 0; i < n; i++) {
            ll use = min(b[i], coupons);
            ll cost = a[i] - use;
            total_gold += cost;
            coupons -= use;
            coupons += cost / c;
        }
        
        cout << total_gold << "\n";
    }
    
    return 0;
}
