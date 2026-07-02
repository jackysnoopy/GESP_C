#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, T;
    cin >> c >> T;
    
    while (T--) {
        int n;
        cin >> n;
        
        vector<int> a(n), b(n), t(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i] >> b[i] >> t[i];
        }
        
        // 基础实现：简单判断
        bool possible = true;
        for (int i = 0; i < n; i++) {
            int distance = abs(b[i] - a[i]);
            if (distance > t[i]) {
                possible = false;
                break;
            }
        }
        
        cout << (possible ? "Yes" : "No") << endl;
    }
    
    return 0;
}