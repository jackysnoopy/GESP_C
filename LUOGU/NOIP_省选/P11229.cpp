#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        // Digital display: each digit uses a certain number of matchsticks.
        // 0:6, 1:2, 2:5, 3:5, 4:4, 5:5, 6:6, 7:3, 8:7, 9:6
        // Use n matchsticks to form the smallest positive integer.
        // Greedy: use as few digits as possible, with smallest leading digit.
        int sticks[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
        if (n < 2) { cout << -1 << "\n"; continue; }
        // Minimum sticks per digit: 2 (digit 1).
        // Maximum digits: n / 2.
        // For the smallest number: minimize number of digits, then minimize lexicographically.
        // Actually, minimize number of digits first (fewer digits = smaller number).
        // Minimum digits: ceil(n / 7) (digit 8 uses 7 sticks).
        // But we need exact n sticks.
        // DP: dp[s] = minimum number of digits to use exactly s sticks.
        // Or: find the minimum number of digits, then construct the smallest number.
        
        // Find minimum digits
        int minDigits = n / 7 + (n % 7 > 0 ? 1 : 0);
        // Try from minDigits to n/2 digits
        for (int d = minDigits; d <= n / 2; d++) {
            // Can we form a d-digit number using exactly n sticks?
            // Each digit uses 2-7 sticks.
            // Total sticks = n. d digits. Average = n/d.
            // If n/d < 2 or n/d > 7: impossible for this d.
            if (n < 2 * d || n > 7 * d) continue;
            // Construct smallest d-digit number with exactly n sticks.
            // First digit: try 1-9 (no leading zero). Smallest first.
            // Remaining d-1 digits: try 0-9. Smallest first.
            vector<int> result(d, 0);
            int remaining = n;
            bool ok = true;
            for (int i = 0; i < d; i++) {
                int start = (i == 0) ? 1 : 0;
                bool found = false;
                for (int digit = start; digit <= 9; digit++) {
                    int remAfter = remaining - sticks[digit];
                    int remDigits = d - i - 1;
                    if (remAfter < 2 * remDigits || remAfter > 7 * remDigits) continue;
                    result[i] = digit;
                    remaining -= sticks[digit];
                    found = true;
                    break;
                }
                if (!found) { ok = false; break; }
            }
            if (ok && remaining == 0) {
                for (int i = 0; i < d; i++) cout << result[i];
                cout << "\n";
                goto done;
            }
        }
        cout << -1 << "\n";
        done:;
    }
    return 0;
}
