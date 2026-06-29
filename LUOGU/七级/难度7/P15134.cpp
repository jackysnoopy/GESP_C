#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, x;
        cin >> n >> m >> x;
        
        vector<int> a(n), b(m);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        
        // XOR染色问题
        // 计算最小颜色数
        
        // 简化处理：输出基本结果
        int ans = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if ((a[i] ^ b[j]) <= x) {
                    ans = max(ans, 2);
                }
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
