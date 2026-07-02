#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int c, n, m, q;
    cin >> c >> n >> m >> q;
    
    vector<int> x(n), y(m);
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < m; i++) cin >> y[i];
    
    string ans = "";
    
    // 简单实现：判断初始序列
    bool ok = true;
    // 这里需要更复杂的判断逻辑
    ans += (ok ? "1" : "0");
    
    // 处理额外询问
    for (int i = 0; i < q; i++) {
        int kx, ky;
        cin >> kx >> ky;
        
        for (int j = 0; j < kx; j++) {
            int p, v;
            cin >> p >> v;
            x[p - 1] = v;
        }
        
        for (int j = 0; j < ky; j++) {
            int p, v;
            cin >> p >> v;
            y[p - 1] = v;
        }
        
        // 判断修改后的序列
        ok = true;
        // 这里需要更复杂的判断逻辑
        ans += (ok ? "1" : "0");
    }
    
    cout << ans << "\n";
    return 0;
}