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
        string X, Y;
        cin >> X >> Y;

        vector<int> cntX(26, 0), cntY(26, 0);
        for (char c : X) cntX[c - 'a']++;
        for (char c : Y) cntY[c - 'a']++;

        bool possible = false;
        string ans = "";

        for (int mask = 1; mask < (1 << 26); mask++) {
            vector<int> chosen(26, 0);
            int total = 0;
            for (int i = 0; i < 26; i++) {
                if (mask & (1 << i)) {
                    chosen[i] = min(cntX[i], 1);
                    total += chosen[i];
                }
            }

            if (total == 0) continue;

            vector<int> combined(26, 0);
            for (int i = 0; i < 26; i++) combined[i] = chosen[i] + cntY[i];

            bool can_make_palindrome = true;
            for (int i = 0; i < 26; i++) {
                if (combined[i] % 2 != 0) {
                    int odd_count = 0;
                    for (int j = 0; j < 26; j++) {
                        if (combined[j] % 2 != 0) odd_count++;
                    }
                    if (odd_count > 1) can_make_palindrome = false;
                    break;
                }
            }

            if (can_make_palindrome) {
                string candidate = "";
                for (int i = 0; i < 26; i++) {
                    for (int j = 0; j < chosen[i]; j++) {
                        candidate += char('a' + i);
                    }
                }
                if (!possible || candidate < ans) {
                    possible = true;
                    ans = candidate;
                }
            }
        }

        if (possible) cout << ans << "\n";
        else cout << "-1\n";
    }

    return 0;
}
