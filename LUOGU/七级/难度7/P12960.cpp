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
        int P;
        string S;
        cin >> P >> S;
        
        // Game Sort问题
        // Amir需要将字符串分成P部分，使得Badari无法排序
        
        int n = S.length();
        
        // 检查是否可能
        bool possible = true;
        
        // 如果P >= n，不可能
        if (P >= n) {
            possible = false;
        }
        
        // 如果所有字符相同，不可能
        bool all_same = true;
        for (int i = 1; i < n; i++) {
            if (S[i] != S[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same && P > 1) {
            possible = false;
        }
        
        if (possible) {
            cout << "Case #" << t << ": POSSIBLE\n";
            
            // 构造分割
            vector<int> splits;
            int part_size = n / P;
            int remainder = n % P;
            
            int pos = 0;
            for (int i = 0; i < P; i++) {
                int len = part_size + (i < remainder ? 1 : 0);
                splits.push_back(len);
            }
            
            // 输出分割
            pos = 0;
            for (int i = 0; i < P; i++) {
                cout << S.substr(pos, splits[i]);
                if (i < P - 1) cout << " ";
                pos += splits[i];
            }
            cout << "\n";
        } else {
            cout << "Case #" << t << ": IMPOSSIBLE\n";
        }
    }
    
    return 0;
}
