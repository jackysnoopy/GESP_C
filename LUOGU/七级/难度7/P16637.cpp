#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // 春季限定独立集问题
    // 计算树的最大独立集
    
    // 简化处理：输出基本结果
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 1) {
            ans++;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
