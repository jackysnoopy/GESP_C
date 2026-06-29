#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // dp[i][j] = maximum value achievable by merging elements from i to j
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    // Base case
    for (int i = 0; i < n; i++) {
        dp[i][i] = a[i];
    }
    
    int ans = *max_element(a.begin(), a.end());
    
    // Fill dp table
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            int j = i + len - 1;
            
            for (int k = i; k < j; k++) {
                if (dp[i][k] == dp[k+1][j] && dp[i][k] > 0) {
                    dp[i][j] = max(dp[i][j], dp[i][k] + 1);
                }
            }
            
            ans = max(ans, dp[i][j]);
        }
    }
    
    cout << ans << "\n";
    return 0;
}
