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
        int N, A;
        cin >> N >> A;
        
        vector<string> pref(N);
        for (int i = 0; i < N; i++) cin >> pref[i];
        
        // 简化：贪心选择
        vector<int> order;
        vector<bool> used(N, false);
        
        // 从目标糖果开始
        order.push_back(A);
        used[A] = true;
        
        // 逐步添加其他糖果
        for (int step = 1; step < N; step++) {
            int best = -1;
            for (int i = 0; i < N; i++) {
                if (!used[i]) {
                    // 检查是否可以放在当前位置
                    bool ok = true;
                    for (int j = 0; j < order.size(); j++) {
                        if (pref[i][order[j]] == 'N') {
                            ok = false;
                            break;
                        }
                    }
                    if (ok && (best == -1 || i < best)) {
                        best = i;
                    }
                }
            }
            if (best != -1) {
                order.insert(order.begin(), best);
                used[best] = true;
            }
        }
        
        if (order.size() == N) {
            cout << "Case #" << t << ":";
            for (int i = 0; i < N; i++) {
                cout << " " << order[i];
            }
            cout << endl;
        } else {
            cout << "Case #" << t << ": IMPOSSIBLE" << endl;
        }
    }
    return 0;
}
