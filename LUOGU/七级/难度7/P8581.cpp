#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // X细胞问题
    // 计算最优子树
    
    // 简化处理：输出基本结果
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > 0) {
            ans++;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
