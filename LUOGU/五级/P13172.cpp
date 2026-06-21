#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, C, M;
        cin >> N >> C >> M;
        
        vector<int> seatCount(N + 1, 0);
        
        for (int i = 0; i < M; i++) {
            int P, B;
            cin >> P >> B;
            seatCount[P]++;
        }
        
        // 计算 prefixSum
        vector<int> prefixSum(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            prefixSum[i] = prefixSum[i-1] + seatCount[i];
        }
        
        // 计算最小 rides K
        int K = 0;
        for (int i = 1; i <= N; i++) {
            // ceil(prefixSum[i] / i)
            int val = (prefixSum[i] + i - 1) / i;
            K = max(K, val);
        }
        
        // 计算 promotions
        int promotions = 0;
        for (int i = 1; i <= N; i++) {
            if (seatCount[i] > K) {
                promotions += seatCount[i] - K;
            }
        }
        
        cout << "Case #" << t << ": " << K << " " << promotions << endl;
    }
    
    return 0;
}
