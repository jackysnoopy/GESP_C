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
        int N;
        cin >> N;
        
        vector<int> order(N);
        for (int i = 0; i < N; i++) {
            cin >> order[i];
            order[i]--;
        }
        
        // Ace in the Hole问题
        // 根据检查顺序推断卡牌值
        
        vector<int> values(N);
        vector<bool> used(N, false);
        
        // 从最后一个检查的卡牌开始推断
        for (int i = N - 1; i >= 0; i--) {
            int pos = order[i];
            
            // 找到最大的未使用值
            for (int v = N - 1; v >= 0; v--) {
                if (!used[v]) {
                    values[pos] = v + 1;
                    used[v] = true;
                    break;
                }
            }
        }
        
        cout << "Case #" << t << ":";
        for (int i = 0; i < N; i++) {
            cout << " " << values[i];
        }
        cout << "\n";
    }
    
    return 0;
}
