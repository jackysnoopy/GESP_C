#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            result = result * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> dp(n + 1, 0);
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] * (i - 1) % MOD;
    }
    
    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        long long term = dp[n - i] * power(dp[i], MOD - 2, MOD) % MOD;
        term = term * power(dp[n - k - i], MOD - 2, MOD) % MOD;
        if (i % 2 == 0) {
            ans = (ans + term) % MOD;
        } else {
            ans = (ans - term + MOD) % MOD;
        }
    }
    
    cout << ans << endl;
    return 0;
}