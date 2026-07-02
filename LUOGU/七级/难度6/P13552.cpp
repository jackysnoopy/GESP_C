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
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // 需要使用 n-k 次 AND 操作，k-1 次加法操作
        // AND 操作会减少值，加法操作会增加值
        
        // 简化：贪心选择
        // 先用 AND 操作合并，再用加法
        
        long long ans = 0;
        
        if (k == 1) {
            // 只能用 AND 操作
            ans = a[0];
            for (int i = 1; i < n; i++) {
                ans &= a[i];
            }
        } else {
            // 可以混合使用
            // 简化处理
            sort(a.begin(), a.end(), greater<int>());
            ans = a[0];
            for (int i = 1; i < min(k, n); i++) {
                ans += a[i];
            }
            for (int i = k; i < n; i++) {
                ans &= a[i];
            }
        }
        
        cout << ans << "\n";
    }
    return 0;
}
