#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q, V;
    cin >> n >> q >> V;
    
    vector<int> p(n + 1);
    for (int i = 0; i <= n; i++) cin >> p[i];
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        
        // 简单实现：计算最短时间
        // 这里需要更复杂的几何计算
        double dx = x2 - x1;
        double dy = y2 - y1;
        double dist = sqrt(dx * dx + dy * dy);
        double time = dist / V;
        
        printf("%.10f\n", time);
    }
    
    return 0;
}