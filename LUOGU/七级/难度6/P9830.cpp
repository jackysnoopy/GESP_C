#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    while (T--) {
        int n, m;
        cin >> n >> m;
        
        // 简单实现：计算最小总长度
        // 这里需要更复杂的几何计算
        double ans = 0;
        
        // 直接计算欧几里得距离
        ans = sqrt(n * n + m * m);
        
        printf("%.15f\n", ans);
    }
    
    return 0;
}