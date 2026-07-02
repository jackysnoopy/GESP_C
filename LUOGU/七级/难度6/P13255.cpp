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
        int N, M, K;
        cin >> N >> M >> K;
        
        // 简化：计算最少石头数
        // 内部点数 = (N-1)*(M-1)
        int interior = (N - 1) * (M - 1);
        
        int ans;
        if (K <= interior) {
            // 需要围住 K 个内部点
            // 最优策略是围成矩形
            ans = 0;
            for (int h = 1; h <= N - 1; h++) {
                for (int w = 1; w <= M - 1; w++) {
                    if (h * w >= K) {
                        int stones = 2 * (h + w);
                        if (ans == 0 || stones < ans) {
                            ans = stones;
                        }
                    }
                }
            }
        } else {
            // 需要额外的石头
            ans = 2 * (N + M - 2);
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    
    return 0;
}
