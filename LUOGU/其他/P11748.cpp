#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    long long fact[21];
    fact[0] = 1;
    for (int i = 1; i <= 20; i++) {
        fact[i] = fact[i-1] * i;
        if (fact[i] > (long long)2e18) fact[i] = (long long)2e18;
    }
    
    while (T--) {
        long long n, S;
        cin >> n >> S;
        
        // Maximize sum_{i=1}^{n} sum_{j=1}^{i} p_j = sum_{i=1}^{n} (n-i+1) * p_i
        // Weight for position i: w_i = n - i + 1
        
        // For n <= 20: enumerate all permutations in lex order up to S
        if (n <= 20 && S >= fact[n]) {
            // Can pick any permutation. Best: place largest values in highest weight positions.
            // Weight is decreasing: position 1 has weight n, position n has weight 1.
            // Optimal: p = (n, n-1, ..., 1)
            long long mod = 998244353;
            long long ans = 0;
            for (long long i = 1; i <= n; i++) {
                ans = (ans + ((n - i + 1) % mod) * (i % mod)) % mod;
            }
            cout << ans << "\n";
            continue;
        }
        
        if (n <= 20) {
            // Enumerate first S permutations in lex order
            vector<int> perm(n);
            for (int i = 0; i < n; i++) perm[i] = i + 1;
            long long best = 0;
            long long count = 0;
            do {
                long long val = 0;
                for (int i = 0; i < n; i++) {
                    val += (long long)(n - i) * perm[i];
                }
                if (val > best) best = val;
                count++;
                if (count >= S) break;
            } while (next_permutation(perm.begin(), perm.end()));
            cout << best << "\n";
            continue;
        }
        
        // n > 20: S < fact[20] <= 20! = 2.43e18
        // The first S permutations all start with 1, 2, ..., up to some prefix.
        // Find the prefix length where all S permutations agree.
        
        // At position i (0-indexed), block size = (n-1-i)!
        // If block >= S, all S permutations have the same value at position i.
        // The value at position i is the (i+1)-th smallest unused value.
        // Since prefix is 1,2,...,i, the value is i+1.
        
        int fixedLen = 0;
        for (int i = 0; i < min(n, (long long)21); i++) {
            long long rem = n - 1 - i;
            if (rem > 20 || fact[rem] >= S) {
                fixedLen = i + 1;
            } else {
                break;
            }
        }
        
        // First fixedLen positions are 1, 2, ..., fixedLen
        // Remaining: n - fixedLen positions with values {fixedLen+1, ..., n}
        // Among these, we consider the first S' = S permutations in lex order of the remaining values.
        // But actually, S permutations of the full array with the first fixedLen fixed.
        // The remaining sub-problem: permutations of {fixedLen+1, ..., n} of length rem = n-fixedLen.
        // S permutations in lex order. rem <= 21.
        
        int rem = n - fixedLen;
        if (rem <= 0) {
            long long mod = 998244353;
            long long ans = 0;
            for (long long i = 1; i <= n; i++) {
                ans = (ans + ((n - i + 1) % mod) * (i % mod)) % mod;
            }
            cout << ans << "\n";
            continue;
        }
        
        long long mod = 998244353;
        long long ans = 0;
        // Fixed prefix contribution
        for (int i = 0; i < fixedLen; i++) {
            ans = (ans + ((n - i) % mod) * ((i + 1) % mod)) % mod;
        }
        
        // For remaining positions: enumerate first S permutations of {fixedLen+1, ..., n}
        // Weight for remaining position j (0-indexed in remaining): n - fixedLen - j
        // Value: fixedLen + 1 + perm_remaining[j] (but perm_remaining is a permutation of {0, 1, ..., rem-1})
        
        vector<int> remPerm(rem);
        for (int i = 0; i < rem; i++) remPerm[i] = i;
        
        long long bestTail = 0;
        long long count = 0;
        do {
            long long val = 0;
            for (int i = 0; i < rem; i++) {
                val += (long long)(rem - i) * (fixedLen + 1 + remPerm[i]);
            }
            if (val > bestTail) bestTail = val;
            count++;
            if (count >= S) break;
        } while (next_permutation(remPerm.begin(), remPerm.end()));
        
        ans = (ans + bestTail) % mod;
        cout << ans << "\n";
    }
    return 0;
}
