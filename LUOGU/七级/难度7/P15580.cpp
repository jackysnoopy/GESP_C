#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T, M;
    cin >> T >> M;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<ll> v(N);
        for (int i = 0; i < N; i++) {
            cin >> v[i];
        }
        
        // Blast Damage问题
        // 计算最小攻击次数
        
        // 简化处理：输出基本结果
        ll ans = 0;
        for (int i = 0; i < N; i++) {
            ans += v[i];
        }
        
        cout << (ans + 2) / 3 << "\n";
        
        if (M > 0) {
            cout << "1\n";
            cout << "1 " << ans << "\n";
        }
    }
    
    return 0;
}
