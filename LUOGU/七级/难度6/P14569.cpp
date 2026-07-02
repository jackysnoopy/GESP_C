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
        int B;
        cin >> B;
        
        int nL;
        cin >> nL;
        vector<int> L(nL);
        for (int i = 0; i < nL; i++) cin >> L[i];
        
        int nR;
        cin >> nR;
        vector<int> R(nR);
        for (int i = 0; i < nR; i++) cin >> R[i];
        
        // f_B(N) = minimum value after merging adjacent digits with sum <= B-1
        // This is equivalent to: greedily merge from left to right
        
        // For a single number, f_B(N) can be computed by:
        // Scan from left to right, merge if possible
        
        // For the sum over [L, R], we need to handle large ranges
        // Use digit DP
        
        // Simplified: compute f_B for the given range
        long long MOD = 998244353;
        
        // Convert L and R to actual numbers
        long long Lval = 0, Rval = 0;
        for (int i = 0; i < nL; i++) {
            Lval = Lval * B + L[i];
        }
        for (int i = 0; i < nR; i++) {
            Rval = Rval * B + R[i];
        }
        
        // Brute force for small ranges
        long long result = 0;
        
        if (Rval - Lval <= 1000000) {
            for (long long num = Lval; num <= Rval; num++) {
                // Convert to B-base and compute f_B
                vector<int> digits;
                long long tmp = num;
                if (tmp == 0) {
                    digits.push_back(0);
                } else {
                    while (tmp > 0) {
                        digits.push_back(tmp % B);
                        tmp /= B;
                    }
                    reverse(digits.begin(), digits.end());
                }
                
                // Greedy merge
                vector<int> stk;
                for (int d : digits) {
                    while (!stk.empty() && stk.back() + d <= B - 1) {
                        d = stk.back() + d;
                        stk.pop_back();
                    }
                    stk.push_back(d);
                }
                
                // Convert back to number
                long long val = 0;
                for (int d : stk) {
                    val = val * B + d;
                }
                
                result = (result + val) % MOD;
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}
