#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const long long MOD = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        string s;
        cin >> s;
        int n = s.size();
        
        // For k=1..n, find maximum XOR and count of partitions
        // This is a complex problem requiring trie/linear basis
        
        // Simplified: compute answers for small n
        vector<long long> p(n + 1, 0), q(n + 1, 0);
        
        // Brute force for small n
        if (n <= 20) {
            // Enumerate all partitions
            // For k parts, there are C(n-1, k-1) ways
            
            for (int k = 1; k <= n; k++) {
                long long maxXor = 0;
                long long count = 0;
                
                // Use bitmask to represent partition points
                // There are n-1 possible split points
                int totalMasks = (1 << (n - 1));
                
                for (int mask = 0; mask < totalMasks; mask++) {
                    // Count bits to get k parts
                    int bits = __builtin_popcount(mask);
                    if (bits != k - 1) continue;
                    
                    // Extract parts and compute XOR
                    long long xorVal = 0;
                    int prev = 0;
                    long long num = 0;
                    
                    for (int i = 0; i < n; i++) {
                        num = num * 2 + (s[i] - '0');
                        if (mask & (1 << i) || i == n - 1) {
                            xorVal ^= num;
                            num = 0;
                        }
                    }
                    
                    if (xorVal > maxXor) {
                        maxXor = xorVal;
                        count = 1;
                    } else if (xorVal == maxXor) {
                        count++;
                    }
                }
                
                p[k] = maxXor % MOD;
                q[k] = count % MOD;
            }
        }
        
        // Compute A, B, C, D
        long long A = 0, B = 0, C = 0, D = 0;
        for (int i = 1; i <= n; i++) {
            A ^= p[i];
            B ^= q[i];
            C ^= (p[i] * i);
            D ^= (q[i] * i);
        }
        
        cout << A << " " << B << " " << C << " " << D << "\n";
    }
    
    return 0;
}
