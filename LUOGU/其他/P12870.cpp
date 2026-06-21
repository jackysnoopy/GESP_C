#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int digitSum(long long x) {
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    cin >> n;
    // Find m >= n with minimum digit sum, then smallest m.
    // Enumerate digit sums from 1 upward, find smallest m >= n for each.
    
    int bestSum = digitSum(n);
    long long bestM = n;
    
    for (int s = 1; s < bestSum; s++) {
        string ns = to_string(n);
        int nd = ns.size();
        
        long long result = -1;
        
        // Try nd digits with sum s, >= n
        if (s >= 1 && s <= 9 * nd) {
            long long cur = 0;
            int rem = s;
            bool exceeded = false;
            bool valid = true;
            
            for (int i = 0; i < nd; i++) {
                int digit = ns[i] - '0';
                int start = digit;
                if (exceeded) start = 0;
                
                bool found_digit = false;
                for (int d = start; d <= 9; d++) {
                    int new_rem = rem - d;
                    int remaining_pos = nd - 1 - i;
                    if (new_rem < 0) break;
                    if (new_rem > 9 * remaining_pos) continue;
                    cur = cur * 10 + d;
                    rem = new_rem;
                    if (d > digit) exceeded = true;
                    found_digit = true;
                    break;
                }
                if (!found_digit) {
                    valid = false;
                    break;
                }
            }
            if (valid && rem == 0) {
                result = cur;
            }
        }
        
        // Try nd+1 digits with sum s
        if (result == -1 && s >= 1 && s <= 9 * (nd + 1)) {
            int first = max(1, s - 9 * nd);
            int rem2 = s - first;
            long long val = first;
            for (int i = 0; i < nd; i++) {
                int left = nd - i;
                int d = max(0, rem2 - 9 * (left - 1));
                val = val * 10 + d;
                rem2 -= d;
            }
            if (rem2 == 0) {
                result = val;
            }
        }
        
        if (result != -1 && result >= n && digitSum(result) == s) {
            bestSum = s;
            bestM = result;
        }
    }
    
    cout << bestM << "\n";
    return 0;
}
