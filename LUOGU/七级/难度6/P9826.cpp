#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    
    while (T--) {
        int n, k;
        cin >> n >> k;
        
        vector<int> a(k), b(k);
        for (int i = 0; i < k; i++) cin >> a[i];
        for (int i = 0; i < k; i++) cin >> b[i];
        
        // 简单实现：计算最小旋转次数
        // 这里需要更复杂的算法
        int ans = 0;
        
        // 排序后计算
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for (int i = 0; i < k; i++) {
            int diff = abs(a[i] - b[i]);
            ans += min(diff, n - diff);
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}