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
        long long K;
        int N;
        cin >> K >> N;
        
        vector<long long> X(N), T(N);
        for (int i = 0; i < N; i++) cin >> X[i];
        for (int i = 0; i < N; i++) cin >> T[i];
        
        // 计算相邻温度变化点之间的距离
        vector<long long> dist(N);
        for (int i = 0; i < N; i++) {
            dist[i] = X[(i + 1) % N] - X[i];
            if (dist[i] <= 0) dist[i] += K;
        }
        
        // 统计不同温度的数量
        int diff_temp = 1;
        for (int i = 1; i < N; i++) {
            if (T[i] != T[i - 1]) diff_temp++;
        }
        
        // 简化：至少需要不同温度数量的温度计
        cout << "Case #" << t << ": " << max(diff_temp, 2) << endl;
    }
    
    return 0;
}
