#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    sort(a.begin(), a.end());
    
    long long ans = 0;
    
    for (int len = 2; len <= n; len += 2) {
        vector<long long> ways(len + 1, 0);
        ways[0] = 1;
        
        for (int i = 0; i < n; i++) {
            vector<long long> newWays(len + 1, 0);
            for (int j = 0; j <= len; j++) {
                if (ways[j] == 0) continue;
                newWays[j] = (newWays[j] + ways[j]) % MOD;
                if (j < len) {
                    newWays[j + 1] = (newWays[j + 1] + ways[j]) % MOD;
                }
            }
            ways = newWays;
        }
        
        long long weight = 0;
        for (int i = 0; i < n - 1; i++) {
            long long diff = (a[i + 1] - a[i]) % MOD;
            weight = (weight + diff * diff % MOD) % MOD;
        }
        
        ans = (ans + weight * ways[len] % MOD) % MOD;
    }
    
    cout << ans << "\n";
    return 0;
}
