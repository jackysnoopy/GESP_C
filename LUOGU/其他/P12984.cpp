#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int tc = 1; tc <= T; tc++) {
        string s;
        cin >> s;
        string result;
        for (int i = 0; i < (int)s.size(); i++) {
            if (i + 1 < (int)s.size() && s[i] <= s[i + 1]) {
                result += s[i];
            } else {
                result += s[i];
                result += s[i];
            }
            if (i + 1 < (int)s.size() && s[i] < s[i + 1]) {
                // Already added once, next char will handle itself
            }
        }
        // Re-think: to get lexicographically smallest, when s[i] <= s[i+1], don't double s[i]
        // when s[i] > s[i+1], double s[i]
        // But wait, need to be careful about the last character
        result.clear();
        for (int i = 0; i < (int)s.size(); i++) {
            bool last = (i == (int)s.size() - 1);
            if (last) {
                result += s[i];
            } else if (s[i] <= s[i + 1]) {
                result += s[i];
            } else {
                result += s[i];
                result += s[i];
            }
        }
        cout << "Case #" << tc << ": " << result << "\n";
    }
    return 0;
}
