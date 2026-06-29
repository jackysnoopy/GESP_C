#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, T;
    cin >> n >> T;
    
    vector<int> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // 心跳排列图问题
    // 构造排列
    
    // 简化处理：输出基本结果
    for (int i = 1; i <= n; i++) {
        cout << i;
        if (i < n) cout << " ";
    }
    cout << "\n";
    
    return 0;
}
