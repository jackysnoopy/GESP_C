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
        
        // 统计关闭的灯数量
        int off = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) off++;
        }
        
        // 简单实现：每次勇士可以打开3盏灯
        // 魔王每次可以关闭2盏灯
        // 需要分析博弈过程
        
        int days = (off + 2) / 3;
        cout << days << "\n";
    }
    
    return 0;
}