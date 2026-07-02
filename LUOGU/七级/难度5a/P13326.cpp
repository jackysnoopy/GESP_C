#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        vector<int> x(n - 1);
        for (int i = 0; i < n - 1; i++) {
            cin >> x[i];
            x[i]--; // 转换为0-indexed
        }
        
        // 基础实现：简单构造
        vector<int> height(n, 10);
        
        // 输出结果
        cout << "Case #" << t << ":";
        for (int i = 0; i < n; i++) {
            cout << " " << height[i];
        }
        cout << endl;
    }
    
    return 0;
}