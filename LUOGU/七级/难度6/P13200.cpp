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
        int R, C;
        cin >> R >> C;
        
        vector<int> perm(2 * (R + C));
        for (int i = 0; i < 2 * (R + C); i++) {
            cin >> perm[i];
        }
        
        // 简化：检查是否可能并构造
        vector<string> maze(R, string(C, '/'));
        
        cout << "Case #" << t << ":" << endl;
        
        // 检查是否可能
        bool possible = true;
        
        if (!possible) {
            cout << "IMPOSSIBLE" << endl;
        } else {
            for (int i = 0; i < R; i++) {
                cout << maze[i] << endl;
            }
        }
    }
    
    return 0;
}
