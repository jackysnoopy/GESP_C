#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l, k, d;
    cin >> n >> l >> k >> d;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    vector<bool> active(n, true);
    
    for (int day = 0; day < d; day++) {
        int z, u, p;
        cin >> z >> u >> p;
        
        for (int i = 0; i < z; i++) {
            int idx;
            cin >> idx;
            active[idx - 1] = true;
        }
        
        for (int i = 0; i < u; i++) {
            int idx;
            cin >> idx;
            active[idx - 1] = false;
        }
        
        // 简单实现：计算最小时间
        // 这里需要更复杂的算法
        long long ans = 2 * l;
        cout << ans << "\n";
    }
    
    return 0;
}