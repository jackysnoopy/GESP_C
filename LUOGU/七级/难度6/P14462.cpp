#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, q;
        cin >> n >> q;
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // Precompute prefix sums and some structure for queries
        // For each query [l, r], we need to compute the answer
        
        // Key insight: each operation takes 2 noodles from 2 buckets and puts them in a 3rd
        // This reduces the number of non-empty buckets by at most 2
        
        // If total noodles = S, non-empty buckets = c
        // Minimum operations = S - max(1, ceil(c/2)) when c >= 2
        
        // For each query, compute:
        // S = sum of a[i] for i in [l,r]
        // c = count of non-zero a[i] for i in [l,r]
        
        // Precompute prefix sums
        vector<long long> prefixSum(n + 1, 0);
        vector<int> prefixNonZero(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + a[i];
            prefixNonZero[i + 1] = prefixNonZero[i] + (a[i] > 0 ? 1 : 0);
        }
        
        while (q--) {
            int l, r;
            cin >> l >> r;
            l--; r--;
            
            long long S = prefixSum[r + 1] - prefixSum[l];
            int c = prefixNonZero[r + 1] - prefixNonZero[l];
            
            if (S == 0) {
                cout << "0\n";
            } else if (c == 1) {
                cout << "0\n";
            } else if (S == 1) {
                cout << "-1\n";
            } else {
                // Answer = S - max(1, (c + 1) / 2)
                long long ans = S - max(1LL, (long long)(c + 1) / 2);
                cout << ans << "\n";
            }
        }
    }
    
    return 0;
}
