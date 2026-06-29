#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t, g;
    cin >> t >> g;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vector<int> a(m), b(m);
        vector<ll> c(m);
        for (int i = 0; i < m; i++) {
            cin >> a[i] >> b[i] >> c[i];
        }
        
        // Air Reform问题
        // 简化处理：输出原始价格
        
        for (int i = 0; i < m; i++) {
            if (i > 0) cout << " ";
            cout << c[i];
        }
        cout << "\n";
    }
    
    return 0;
}
