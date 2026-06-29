#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

long long play_game(long long N, int Q, long long K, vector<long long> L, vector<long long> R) {
    // 跳跃游戏问题
    // N个踏板，可以选择走一步(到i+1)或跳跃(到i+K，得分+A[i])
    // 使用差分数组处理区间加操作
    
    vector<ll> diff(N + 2, 0);
    for (int i = 0; i < Q; i++) {
        diff[L[i]] += 1;
        diff[R[i] + 1] -= 1;
    }
    
    // 计算每个踏板的A[i]
    vector<ll> A(N, 0);
    ll cur = 0;
    for (int i = 0; i < N; i++) {
        cur += diff[i];
        A[i] = cur;
    }
    
    // 动态规划
    // dp[i] = 从0出发到i的最大得分
    vector<ll> dp(N + 1, -1);
    dp[0] = 0;
    
    for (int i = 0; i < N; i++) {
        if (dp[i] < 0) continue;
        
        // 走一步
        if (i + 1 <= N) {
            dp[i + 1] = max(dp[i + 1], dp[i]);
        }
        
        // 跳跃
        if (i + K <= N) {
            dp[i + K] = max(dp[i + K], dp[i] + A[i]);
        }
    }
    
    // 返回从0出发到N或更远的最大得分
    ll ans = 0;
    for (int i = N; i <= N; i++) {
        ans = max(ans, dp[i]);
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N, K;
    int Q;
    cin >> N >> Q >> K;
    
    vector<ll> L(Q), R(Q);
    for (int i = 0; i < Q; i++) {
        cin >> L[i] >> R[i];
    }
    
    cout << play_game(N, Q, K, L, R) << "\n";
    
    return 0;
}
