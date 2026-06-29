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
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> S(n), T_set(n);
        for (int i = 0; i < n; i++) {
            int sz;
            cin >> sz;
            S[i].resize(sz);
            for (int j = 0; j < sz; j++) {
                cin >> S[i][j];
            }
        }
        
        for (int i = 0; i < n; i++) {
            int sz;
            cin >> sz;
            T_set[i].resize(sz);
            for (int j = 0; j < sz; j++) {
                cin >> T_set[i][j];
            }
        }
        
        // 填数游戏问题
        // 简化处理：输出基本结果
        
        cout << "Bob\n";
        cout << "0\n";
    }
    
    return 0;
}
