#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 10007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> L(n);
    long long total = 0;
    for (int i = 0; i < n; i++) {
        cin >> L[i];
        total += L[i];
    }
    
    // Binary search on minimum maximum segment length
    int low = *max_element(L.begin(), L.end());
    int high = total;
    int answer = high;
    
    while (low <= high) {
        int mid = (low + high) / 2;
        
        // Check if we can split into segments with max length <= mid
        int cuts = 0;
        long long cur_sum = 0;
        
        for (int i = 0; i < n; i++) {
            if (cur_sum + L[i] > mid) {
                cuts++;
                cur_sum = L[i];
            } else {
                cur_sum += L[i];
            }
        }
        
        if (cuts <= m) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    // Count number of ways to achieve minimum
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + L[i];
    }
    
    // DP to count ways
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 2, 0));
    vector<vector<long long>> sum_dp(n + 1, vector<long long>(m + 2, 0));
    
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        sum_dp[0][i] = dp[0][i - 1];
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= min(i, m + 1); j++) {
            // Find the range of valid previous positions
            int left = 0, right = i - 1;
            while (left < right) {
                int mid = (left + right) / 2;
                if (prefix[i] - prefix[mid] <= answer) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }
            
            if (prefix[i] - prefix[left] <= answer) {
                dp[i][j] = (sum_dp[left][j - 1] - (left > 0 ? sum_dp[left - 1][j - 1] : 0) + MOD) % MOD;
            }
        }
        
        for (int j = 0; j <= m + 1; j++) {
            sum_dp[i][j] = (sum_dp[i - 1][j] + dp[i][j]) % MOD;
        }
    }
    
    long long ways = 0;
    for (int j = 1; j <= m + 1; j++) {
        ways = (ways + dp[n][j]) % MOD;
    }
    
    cout << answer << " " << ways << "\n";
    return 0;
}
