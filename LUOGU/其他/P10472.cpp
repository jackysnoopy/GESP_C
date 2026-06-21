#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();
    vector<int> dp(n, 0);
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if ((s[i] == ')' && s[i - 1] == '(') ||
            (s[i] == ']' && s[i - 1] == '[') ||
            (s[i] == '}' && s[i - 1] == '{')) {
            dp[i] = 2 + (i >= 2 ? dp[i - 2] : 0);
        } else if ((s[i] == ')' && s[i - 1] == ']') ||
                   (s[i] == ']' && s[i - 1] == '}') ||
                   (s[i] == '}' && s[i - 1] == '(')) {
            int pos = i - 1 - dp[i - 1];
            if (pos >= 0 && ((s[i] == ')' && s[pos] == '(') ||
                             (s[i] == ']' && s[pos] == '[') ||
                             (s[i] == '}' && s[pos] == '{'))) {
                dp[i] = dp[i - 1] + 2 + (pos >= 2 ? dp[pos - 2] : 0);
            }
        }
        if (dp[i] > ans) ans = dp[i];
    }
    cout << ans << '\n';
    return 0;
}
