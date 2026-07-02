#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int K, N;
        cin >> K >> N;
        
        vector<int> keys(K);
        for (int i = 0; i < K; i++) cin >> keys[i];
        
        vector<int> chest_type(N);
        vector<vector<int>> chest_keys(N);
        
        for (int i = 0; i < N; i++) {
            int T_i, K_i;
            cin >> T_i >> K_i;
            chest_type[i] = T_i;
            chest_keys[i].resize(K_i);
            for (int j = 0; j < K_i; j++) cin >> chest_keys[i][j];
        }
        
        // 贪心：每次选择能打开的最小编号宝箱
        vector<bool> opened(N, false);
        vector<int> order;
        vector<int> have = keys;
        
        for (int step = 0; step < N; step++) {
            int best = -1;
            for (int i = 0; i < N; i++) {
                if (!opened[i]) {
                    // 检查是否有对应钥匙
                    bool can_open = false;
                    for (int k : have) {
                        if (k == chest_type[i]) {
                            can_open = true;
                            break;
                        }
                    }
                    if (can_open && (best == -1 || i < best)) {
                        best = i;
                    }
                }
            }
            
            if (best == -1) {
                order.clear();
                break;
            }
            
            opened[best] = true;
            order.push_back(best + 1);
            
            // 移除使用的钥匙
            for (int j = 0; j < have.size(); j++) {
                if (have[j] == chest_type[best]) {
                    have.erase(have.begin() + j);
                    break;
                }
            }
            
            // 添加宝箱内的钥匙
            for (int k : chest_keys[best]) {
                have.push_back(k);
            }
        }
        
        if (order.empty()) {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        } else {
            cout << "Case #" << t << ":";
            for (int i = 0; i < N; i++) {
                cout << " " << order[i];
            }
            cout << endl;
        }
    }
    return 0;
}
