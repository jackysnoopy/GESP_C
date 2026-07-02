#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // For small n (brute force)
    // For each pair (i,j) with i < j, we can merge them
    // The operation x ⊖ y is equivalent to x XOR y (binary subtraction without borrow)
    
    // Key observation: x ⊖ y = x XOR y
    // So the problem becomes: given a multiset, repeatedly pick two numbers and replace with their XOR
    // The maximum value we can get is the maximum XOR subset (linear basis)
    
    // For the sum over all intervals, we need to compute for each [l,r] the maximum XOR subset
    
    // Brute force O(n^2 * n * log MAX)
    long long MOD = 998244353;
    long long result = 0;
    
    for (int l = 0; l < n; l++) {
        // Linear basis
        vector<long long> basis(25, 0);
        for (int r = l; r < n; r++) {
            // Insert a[r] into basis
            long long x = a[r];
            for (int b = 24; b >= 0; b--) {
                if ((x >> b) & 1) {
                    if (basis[b] == 0) {
                        basis[b] = x;
                        break;
                    }
                    x ^= basis[b];
                }
            }
            
            // Get maximum XOR value from basis
            long long maxXor = 0;
            for (int b = 24; b >= 0; b--) {
                maxXor = max(maxXor, maxXor ^ basis[b]);
            }
            
            result = (result + maxXor) % MOD;
        }
    }
    
    cout << result << "\n";
    return 0;
}
