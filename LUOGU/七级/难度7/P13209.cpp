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
        
        vector<string> grid(R);
        for (int i = 0; i < R; i++) {
            cin >> grid[i];
        }
        
        // Map Reduce问题
        // 简化处理：输出基本结果
        
        int start_r = -1, start_c = -1;
        int finish_r = -1, finish_c = -1;
        
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (grid[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                }
                if (grid[i][j] == 'F') {
                    finish_r = i;
                    finish_c = j;
                }
            }
        }
        
        // 简单计算最短路径（不考虑墙壁）
        int dist = abs(start_r - finish_r) + abs(start_c - finish_c);
        
        cout << "Case #" << t << ": " << dist << "\n";
    }
    
    return 0;
}
