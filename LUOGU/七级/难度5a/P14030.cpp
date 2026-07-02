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
        int n;
        cin >> n;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // 基础实现：简单构造
        // 输出恒等排列作为占位
        cout << 0 << endl;
        for (int i = 1; i <= n; i++) {
            if (i > 1) cout << " ";
            cout << i;
        }
        cout << endl;
    }
    
    return 0;
}