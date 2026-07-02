#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    
    long long x0, d;
    cin >> x0 >> d;
    
    int m;
    cin >> m;
    
    // 简化版本：对每个选手计算最小能量
    for (int j = 0; j < m; j++) {
        long long t;
        cin >> t;
        
        // 贪心：从最近的补给点开始
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            // 找到最近的补给点
            long long nearest = x0;
            long long dist = abs(x[i] - x0);
            
            // 检查其他补给点
            for (long long k = -5; k <= 5; k++) {
                long long supply = x0 + k * d;
                long long throw_dist = abs(x[i] - supply);
                long long move_cost = abs(k) * t;
                if (throw_dist * throw_dist + move_cost < dist * dist + move_cost) {
                    nearest = supply;
                    dist = throw_dist;
                }
            }
            
            ans += dist * dist;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
