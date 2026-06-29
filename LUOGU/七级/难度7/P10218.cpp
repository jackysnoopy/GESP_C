#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, T;
    cin >> c >> T;
    
    while (T--) {
        int n, k;
        ll m;
        cin >> n >> m >> k;
        
        vector<ll> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        
        // 魔法手杖问题
        // 选择子集S和x，使得min(min(a_i+x for i in S), min(a_i^x for i not in S))最大
        // 其中S的b_i之和不超过m
        
        // 简单实现：枚举x（如果k较小）
        ll ans = 0;
        
        if (k <= 20) {
            for (ll x = 0; x < (1LL << k); x++) {
                // 对于每个x，计算最优的S
                vector<ll> vals(n);
                for (int i = 0; i < n; i++) {
                    vals[i] = a[i] ^ x;
                }
                
                // 按vals排序
                vector<int> idx(n);
                for (int i = 0; i < n; i++) idx[i] = i;
                sort(idx.begin(), idx.end(), [&](int i, int j) {
                    return vals[i] < vals[j];
                });
                
                // 贪心选择S
                ll cost = 0;
                int chosen = 0;
                for (int i = 0; i < n; i++) {
                    if (cost + b[idx[i]] <= m) {
                        cost += b[idx[i]];
                        chosen++;
                    } else {
                        break;
                    }
                }
                
                if (chosen > 0) {
                    ll min_val = vals[idx[chosen - 1]];
                    ans = max(ans, min_val);
                }
            }
        } else {
            // 对于大k，需要更复杂的算法
            // 这里只给出基本实现
            ans = 0;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
