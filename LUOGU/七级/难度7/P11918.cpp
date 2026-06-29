#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, t;
    cin >> n >> t;
    
    vector<double> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    
    // 考试问题：选择作答的题目，使得不挂科的概率最大
    // 需要获得至少t分
    
    // 贪心：选择正确概率最高的题目作答
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int i, int j) {
        return p[i] > p[j];
    });
    
    // 计算不挂科的概率
    // 使用动态规划
    vector<double> dp(t + 1, 0);
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        vector<double> new_dp(t + 1, 0);
        
        for (int j = 0; j <= t; j++) {
            if (dp[j] == 0) continue;
            
            // 不作答
            new_dp[j] = max(new_dp[j], dp[j]);
            
            // 作答正确
            if (j + 1 <= t) {
                new_dp[j + 1] = max(new_dp[j + 1], dp[j] * p[id]);
            }
            
            // 作答错误
            if (j - 1 >= 0) {
                new_dp[j - 1] = max(new_dp[j - 1], dp[j] * (1 - p[id]));
            }
        }
        
        dp = new_dp;
    }
    
    double ans = 0;
    for (int j = t; j <= t; j++) {
        ans = max(ans, dp[j]);
    }
    
    cout << fixed << setprecision(20) << ans << "\n";
    
    return 0;
}
