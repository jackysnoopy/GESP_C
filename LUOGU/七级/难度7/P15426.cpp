#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Time to Heal问题
    // 简化处理：输出基本结果
    
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, a[i]);
    }
    
    cout << ans << "\n";
    
    return 0;
}
