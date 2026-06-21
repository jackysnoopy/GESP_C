#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size();
    // Fill ? with 0 or 1 to maximize non-overlapping "00" and "11" substrings.
    // Greedy: scan left to right. When we see two same chars, count and skip.
    // For ?: try to match the previous character.
    int ans = 0;
    int i = 0;
    while (i < n - 1) {
        char c1 = s[i], c2 = s[i + 1];
        if (c1 == '?') {
            // Look back to see what c1 should be
            if (i > 0 && s[i - 1] != '?') c1 = s[i - 1];
            else c1 = '0'; // arbitrary
        }
        if (c2 == '?') {
            c2 = c1; // try to match
        }
        if (c1 == c2 && c1 != '?') {
            ans++;
            i += 2;
        } else {
            i++;
        }
    }
    cout << ans << endl;
    return 0;
}
