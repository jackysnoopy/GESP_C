#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        string C, J;
        cin >> C >> J;

        int n = C.size();
        long long best_diff = 1e18;
        string best_c = "", best_j = "";

        for (long long c_val = 0; c_val < (1LL << (n * 4)); c_val++) {
            string c_str = "";
            long long temp = c_val;
            for (int i = 0; i < n; i++) {
                c_str = char('0' + (temp % 10)) + c_str;
                temp /= 10;
            }

            bool valid_c = true;
            for (int i = 0; i < n; i++) {
                if (C[i] != '?' && C[i] != c_str[i]) {
                    valid_c = false;
                    break;
                }
            }
            if (!valid_c) continue;

            for (long long j_val = 0; j_val < (1LL << (n * 4)); j_val++) {
                string j_str = "";
                long long temp2 = j_val;
                for (int i = 0; i < n; i++) {
                    j_str = char('0' + (temp2 % 10)) + j_str;
                    temp2 /= 10;
                }

                bool valid_j = true;
                for (int i = 0; i < n; i++) {
                    if (J[i] != '?' && J[i] != j_str[i]) {
                        valid_j = false;
                        break;
                    }
                }
                if (!valid_j) continue;

                long long c_num = stoll(c_str);
                long long j_num = stoll(j_str);
                long long diff = abs(c_num - j_num);

                if (diff < best_diff || (diff == best_diff && c_num < stoll(best_c)) || (diff == best_diff && c_num == stoll(best_c) && j_num < stoll(best_j))) {
                    best_diff = diff;
                    best_c = c_str;
                    best_j = j_str;
                }
            }
        }

        cout << "Case #" << t << ": " << best_c << " " << best_j << "\n";
    }

    return 0;
}
