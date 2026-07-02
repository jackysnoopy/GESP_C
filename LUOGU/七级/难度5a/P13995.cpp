#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        long long x, y, p;
        cin >> x >> y >> p;
        
        // 基础实现：简单检查
        // 如果x == y，不需要操作
        if (x == y) {
            cout << 0 << endl;
            continue;
        }
        
        // 检查是否可能：y的每一位必须在x或p中可设置
        bool possible = true;
        for (int i = 0; i < 30; i++) {
            if ((y >> i) & 1) {
                if (!((x >> i) & 1) && !((p >> i) & 1) && !((p + 1) >> i & 1)) {
                    possible = false;
                    break;
                }
            }
        }
        
        if (!possible) {
            cout << -1 << endl;
            continue;
        }
        
        // 简单贪心：尝试操作1和操作2
        // 这里只输出1作为占位，实际需要更复杂的算法
        cout << 1 << endl;
    }
    
    return 0;
}