#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 998244353;
const int BASE = 233;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, l, r, X;
    cin >> m >> l >> r >> X;
    
    string s;
    cin >> s;
    
    // Count occurrences
    int extra = 0;
    for (char c : s) {
        if (c == '1') extra++;
    }
    
    // Simplified calculation
    long long ans = 0;
    
    for (int k = l; k <= r; k++) {
        // Calculate f(k) - maximum number of intervals with mex >= k
        long long fk = 0;
        
        // For small k, most intervals qualify
        if (k == 0) {
            fk = (long long)(m * X + extra) * (m * X + extra + 1) / 2;
        } else if (k <= m) {
            // Intervals that contain all numbers 0 to k-1
            fk = (long long)(m * X + extra - k) * (m * X + extra - k + 1) / 2;
        }
        
        // Calculate contribution
        long long power = 1;
        for (int i = 0; i < k; i++) {
            power = (power * BASE) % MOD;
        }
        
        ans ^= (power * fk) % MOD;
    }
    
    cout << ans << endl;
    
    return 0;
}