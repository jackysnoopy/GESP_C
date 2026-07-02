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
        int N, K;
        cin >> N >> K;
        
        int m = N - K + 1;
        vector<long long> sum(m);
        for (int i = 0; i < m; i++) {
            cin >> sum[i];
        }
        
        // 简单策略：计算最大值和最小值的差
        long long min_sum = *min_element(sum.begin(), sum.end());
        long long max_sum = *max_element(sum.begin(), sum.end());
        
        // 最小可能的差值
        long long ans = (max_sum - min_sum) / K;
        
        cout << "Case #" << t << ": " << ans << "\n";
    }
    
    return 0;
}