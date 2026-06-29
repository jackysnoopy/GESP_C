#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector<ll> x(m);
        for (int i = 0; i < m; i++) {
            cin >> x[i];
        }
        
        // 算术练习问题
        // 每次操作 a[j] = x[i] - a[j]
        // 使得最终数组和最大
        
        // 贪心：每次选择使和增加最多的操作
        ll sum = 0;
        vector<ll> a(n, 0);
        
        for (int i = 0; i < m; i++) {
            // 选择使和增加最多的j
            ll best_j = 0;
            ll best_delta = x[i] - 2 * a[0];
            
            for (int j = 1; j < n; j++) {
                ll delta = x[i] - 2 * a[j];
                if (delta > best_delta) {
                    best_delta = delta;
                    best_j = j;
                }
            }
            
            a[best_j] = x[i] - a[best_j];
        }
        
        ll total = accumulate(a.begin(), a.end(), 0LL);
        cout << total << "\n";
    }
    
    return 0;
}
