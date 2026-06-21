#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int q; cin >> q;
    while (q--) {
        int a2, a3, a4, b4, b6; cin >> a2 >> a3 >> a4 >> b4 >> b6;
        int best = 0;
        // Brute force all assignments
        for (int i = 0; i <= min(a4, b4); i++) {
            for (int j = 0; j <= min(a4 - i, b6); j++) {
                for (int k = 0; k <= min(a3, b6 - j); k++) {
                    for (int l = 0; l <= min(a3 - k, (b6 - j - k) / 2); l++) {
                        int rem_b6 = b6 - j - k - 2 * l;
                        int rem_a4 = a4 - i - j;
                        int rem_a3 = a3 - k - 2 * l;
                        // 4-dorms left: can only go in 4-tables
                        int t4 = min(rem_a4, b4 - i);
                        // 3-dorms left: need 3+3 in 6-tables
                        int t6_33 = min(rem_a3 / 2, rem_b6);
                        int rem_a3_2 = rem_a3 - 2 * t6_33;
                        int rem_b6_2 = rem_b6 - t6_33;
                        // 3+2 in 6-tables
                        int t6_32 = min(rem_a3_2, min(a2, rem_b6_2));
                        int rem_a3_3 = rem_a3_2 - t6_32;
                        int rem_a2_1 = a2 - t6_32;
                        int rem_b6_3 = rem_b6_2 - t6_32;
                        // 2+2 in 4-tables
                        int t4_22 = min(rem_a2_1 / 2, b4 - i - t4);
                        int rem_a2_2 = rem_a2_1 - 2 * t4_22;
                        // 2+2+2 in 6-tables
                        int t6_222 = min(rem_a2_2 / 3, rem_b6_3);
                        int rem_a2_3 = rem_a2_2 - 3 * t6_222;
                        int rem_b6_4 = rem_b6_3 - t6_222;
                        // 2+2 in 6-tables
                        int t6_22 = min(rem_a2_3 / 2, rem_b6_4);
                        int rem_a2_4 = rem_a2_3 - 2 * t6_22;
                        int rem_b6_5 = rem_b6_4 - t6_22;
                        // 2 in 6-tables
                        int t6_2 = min(rem_a2_4, rem_b6_5);
                        int seated = 4*i + 4*j + 3*k + 6*l + 4*t4 + 6*t6_33 + 5*t6_32 + 4*t4_22 + 6*t6_222 + 4*t6_22 + 2*t6_2;
                        best = max(best, seated);
                    }
                }
            }
        }
        cout << best << "\n";
    }
    return 0;
}
