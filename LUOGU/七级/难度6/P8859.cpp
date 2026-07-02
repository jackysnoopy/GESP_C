#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXN = 1005;
long long dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k, type;
    cin >> n >> k >> type;
    
    // Simplified DP approach
    // dp[i][j] = number of permutations of length i with f(A) = j
    
    dp[1][0] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            // Transition: add element i at different positions
            for (int pos = 0; pos < i; pos++) {
                int new_j = j + (i - 1 - pos);
                if (new_j <= k) {
                    dp[i][new_j] = (dp[i][new_j] + dp[i-1][j]) % MOD;
                }
            }
        }
    }
    
    cout << dp[n][k] << endl;
    
    return 0;
}