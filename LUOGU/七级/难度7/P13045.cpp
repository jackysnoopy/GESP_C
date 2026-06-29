#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Ropes问题（交互题）
    // 简化版本：只输出基本结果
    
    int T, N, W;
    cin >> T >> N >> W;
    
    for (int t = 0; t < T; t++) {
        for (int i = 0; i < N; i++) {
            // 简单策略：连接对称位置
            int A = i + 1;
            int B = N - i;
            cout << A << " " << B << endl;
            
            // 读取对手的移动
            int C, D;
            cin >> C >> D;
        }
    }
    
    return 0;
}
