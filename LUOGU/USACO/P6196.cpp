#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    cin >> n >> k;
    // Count inversions of permutation of 1..n that have exactly k inversions
    // This is a classic DP problem
    // dp[i][j] = # of permutations of 1..i with j inversions
    // dp[i][j] = sum dp[i-1][j-k] for k=0..i-1
    // Use prefix sums for efficiency
    int maxInv = n*(n-1)/2;
    if (k > maxInv) { cout << 0 << "\n"; return 0; }
    vector<long long> dp(k+1, 0);
    dp[0] = 1;
    for (int i = 2; i <= n; i++) {
        vector<long long> ndp(k+1, 0);
        vector<long long> ps(k+1, 0);
        for (int j = 0; j <= k; j++) ps[j] = (j>0?ps[j-1]:0) + dp[j];
        for (int j = 0; j <= k; j++) {
            int lo = max(0, j-(i-1));
            ndp[j] = ps[j] - (lo>0?ps[lo-1]:0);
        }
        dp = ndp;
    }
    cout << dp[k] << "\n";
    return 0;
}
