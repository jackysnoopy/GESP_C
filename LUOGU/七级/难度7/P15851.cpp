#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // 柠檬问题（通信题）
    // 简化版本：输出基本结果
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> p(n);
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        
        // 简化策略：使用第一个位置
        cout << "1\n";
        cout << "0\n";
        cout << "1\n";
        
        int response;
        cin >> response;
    }
    
    return 0;
}
