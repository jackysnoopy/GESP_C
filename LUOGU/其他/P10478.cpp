#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M; cin >> N >> M;
    vector<int> a(N), b;
    for (int i = 0; i < N; i++) cin >> a[i];
    
    // 压缩相邻正数
    int sum = a[0];
    for (int i = 1; i < N; i++) {
        if (a[i] * a[i-1] >= 0) sum += a[i];
        else { b.push_back(sum); sum = a[i]; }
    }
    b.push_back(sum);
    
    int n = b.size();
    vector<vector<long long>> dp(n + 1, vector<long long>(M + 1, LLONG_MIN / 2));
    for (int i = 0; i <= n; i++) dp[i][0] = 0;
    
    for (int j = 1; j <= M; j++) {
        long long best = LLONG_MIN / 2;
        for (int i = j; i <= n; i++) {
            best = max(best, dp[i-1][j-1]);
            dp[i][j] = max(dp[i-1][j], best + b[i-1]);
        }
    }
    
    long long ans = 0;
    for (int j = 1; j <= M; j++) ans = max(ans, dp[n][j]);
    cout << ans << "\n";
    return 0;
}