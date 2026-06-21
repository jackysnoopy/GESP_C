#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, A, B;
        cin >> N >> A >> B;
        
        vector<int> U(N + 1);
        for (int i = 1; i <= N; i++) {
            cin >> U[i];
        }
        
        // 尝试从最小的金属开始，检查是否能满足需求
        bool found = false;
        for (int start = 1; start <= 500; start++) {
            vector<int> have(N + 1, 0);
            have[start] = 1;
            
            // 从大到小处理金属
            for (int i = start; i > 0; i--) {
                if (have[i] == 0) continue;
                
                // 如果是需要的金属，减少需求
                if (i <= N) {
                    int use = min(have[i], U[i]);
                    U[i] -= use;
                    have[i] -= use;
                }
                
                // 使用炼金术
                if (i > A) {
                    have[i - A] += have[i];
                }
                if (i > B) {
                    have[i - B] += have[i];
                }
                have[i] = 0;
            }
            
            // 检查是否满足所有需求
            bool ok = true;
            for (int i = 1; i <= N; i++) {
                if (U[i] > 0) {
                    ok = false;
                    break;
                }
            }
            
            if (ok) {
                cout << "Case #" << t << ": " << start << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        }
    }
    
    return 0;
}
