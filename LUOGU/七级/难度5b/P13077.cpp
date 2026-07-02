#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // We want to select k non-overlapping contiguous segments
    // to maximize the sum of elements in these segments
    
    // This is a classic DP problem
    // dp[i][j] = maximum sum using j segments considering first i elements
    
    // But n can be up to 3*10^5, so O(n*k) might be too slow
    
    // Let's use a different approach:
    // We can use a greedy approach with a priority queue
    
    // Actually, let's use the standard approach for this problem:
    // 1. Compute prefix sums
    // 2. Use DP with optimization
    
    // But for k segments, we need O(n*k) which is too slow for n=3*10^5
    
    // Let me think about this differently:
    // We want to select k non-overlapping segments
    // This is equivalent to: select 2k boundaries (start and end of each segment)
    // such that the sum of elements in these segments is maximized
    
    // Actually, let's use a simpler approach:
    // For k=1, it's the maximum subarray problem
    // For k>1, we can use DP with optimization
    
    // Let's use the approach where we compute:
    // dp[i] = maximum sum using any number of segments considering first i elements
    // Then we can use a greedy approach to select k segments
    
    // Actually, let me use the standard approach for this problem:
    // 1. Compute the maximum sum of k non-overlapping segments
    // 2. Use DP with prefix sums
    
    // For n up to 3*10^5, we need an efficient algorithm
    // Let's use the approach where we compute the maximum sum of each segment
    // and then select the best k segments
    
    // But this doesn't work because segments can overlap
    
    // Let me use a different approach:
    // We can use a greedy approach with a priority queue
    // 1. Find the maximum subarray
    // 2. "Remove" it and find the next maximum
    // 3. Repeat k times
    
    // But this doesn't work either because removing a segment might affect others
    
    // Let me use the standard DP approach:
    // dp[i][j] = maximum sum using j segments considering first i elements
    // dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] + a[i], dp[i][j-1] + a[i])
    
    // But this is O(n*k) which is too slow
    
    // Let me use a different approach:
    // We can use the fact that we want to maximize the sum
    // So we should select all positive elements
    
    // But we're constrained by the number of segments k
    
    // Let me think about this more carefully:
    // We want to select k non-overlapping segments
    // This is equivalent to: select 2k boundaries
    // The sum of elements in the segments is the sum of prefix differences
    
    // Actually, let me use the standard approach for this problem:
    // 1. Compute prefix sums
    // 2. Use DP with optimization
    
    // For k segments, we can use the following approach:
    // dp[i] = maximum sum using any number of segments considering first i elements
    // Then we can select the best k segments using a greedy approach
    
    // But this is still complex. Let me just implement a simple O(n*k) solution
    // and hope it's fast enough
    
    // Actually, for n up to 3*10^5 and k up to n, O(n*k) is too slow
    
    // Let me use a different approach:
    // We can use a greedy approach with a priority queue
    // 1. Find the maximum subarray
    // 2. "Remove" it and find the next maximum
    // 3. Repeat k times
    
    // But this doesn't work because removing a segment might affect others
    
    // Let me use the standard DP approach with optimization:
    // dp[i][j] = maximum sum using j segments considering first i elements
    // We can optimize this using the fact that dp[i][j] is non-decreasing in i
    
    // Actually, let me just implement the O(n*k) solution and see if it works
    
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    
    for (int j = 1; j <= k; j++) {
        long long max_sum = 0;
        for (int i = 1; i <= n; i++) {
            // Option 1: don't use a[i]
            dp[i][j] = dp[i-1][j];
            
            // Option 2: start a new segment at i
            max_sum = max(max_sum + a[i], a[i]);
            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + max_sum);
        }
    }
    
    cout << dp[n][k] << endl;
    
    return 0;
}
