#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p;
    cin >> n >> p;
    // Find n-digit number x where digit_sum(x) % p is minimized,
    // then x is minimized.
    // n <= 7, p <= 100. n-digit: from 10^(n-1) to 10^n - 1.
    // Max digit sum = 9*n <= 63. So digit_sum % p < p.
    // Since n <= 7, enumerate digit sums from 0 upward.
    // For each target remainder r (0, 1, 2, ...):
    //   Find smallest n-digit number with digit_sum % p == r.
    //   The target digit sum s satisfies s % p == r and 1 <= s <= 9*n.
    //   (s >= 1 because first digit >= 1)
    //
    // For a given digit sum s, the smallest n-digit number with that sum:
    //   First digit: max(1, s - 9*(n-1)) [must leave enough for remaining digits]
    //   Remaining digits (n-1 of them): fill from left with smallest possible.
    //   Remaining sum = s - first_digit. Distribute to rightmost digits.
    //
    // Enumerate r from 0 to p-1. For each r, find smallest s >= 1 with s % p == r
    // and s <= 9*n. If s < 1, try s + p, s + 2p, ...
    // Then construct the number.
    
    int maxSum = 9 * n;
    for (int r = 0; r < p; r++) {
        // Find smallest s in [1, maxSum] with s % p == r
        int s = r;
        if (s == 0) s = p; // s must be >= 1
        if (s < 1) s += p;
        while (s <= maxSum) {
            // Construct smallest n-digit number with digit sum s
            int first = max(1, s - 9 * (n - 1));
            int rem = s - first;
            // Fill remaining n-1 digits: smallest number = leftmost smallest
            // Each digit: max(0, rem - 9*(remaining-1)) to min(9, rem)
            string result = "";
            result += (char)('0' + first);
            int remaining = rem;
            for (int d = 0; d < n - 1; d++) {
                int left = n - 1 - d;
                int dig = max(0, remaining - 9 * (left - 1));
                result += (char)('0' + dig);
                remaining -= dig;
            }
            cout << result << "\n";
            return 0;
        }
        // If no s found for this r, try next r
    }
    // Should never reach here
    return 0;
}
