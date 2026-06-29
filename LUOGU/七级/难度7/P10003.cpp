#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q, V;
    cin >> n >> q >> V;
    
    vector<ll> p(n + 1);
    for (int i = 0; i <= n; i++) cin >> p[i];
    
    vector<ll> v(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> v[i];
    
    while (q--) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // 找到x1和x2所在的传送带编号
        int band1 = 0, band2 = 0;
        for (int i = 0; i < n; i++) {
            if (x1 >= p[i] && x1 < p[i + 1]) band1 = i + 1;
            if (x2 >= p[i] && x2 < p[i + 1]) band2 = i + 1;
        }
        
        // 简化处理：计算最小时间
        // x方向移动时间
        double dx = abs(x2 - x1);
        double tx = dx / V;
        
        // y方向：考虑传送带速度
        double dy = y2 - y1;
        double ty;
        
        if (band1 == band2) {
            // 在同一个传送带区域
            double effective_v = v[band1];
            ty = dy / (V + effective_v);
            if (ty < 0) ty = dy / (V - effective_v);
        } else {
            // 不同传送带区域
            double effective_v1 = v[band1];
            double effective_v2 = v[band2];
            ty = dy / (V + (effective_v1 + effective_v2) / 2);
        }
        
        double ans = max(tx, abs(ty));
        printf("%.10f\n", ans);
    }
    
    return 0;
}
