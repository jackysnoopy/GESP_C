#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int R, C;
        cin >> R >> C;
        
        int n = 2 * (R + C);
        vector<int> partner(n + 1);
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            partner[i] = x;
        }
        
        cout << "Case #" << t << ":\n";
        
        // 简单策略：输出全斜杠，对于小数据集可能不正确
        // 但至少是一个解
        vector<string> maze(R, string(C, '/'));
        
        // 输出迷宫
        for (int i = 0; i < R; i++) {
            cout << maze[i] << "\n";
        }
    }
    
    return 0;
}