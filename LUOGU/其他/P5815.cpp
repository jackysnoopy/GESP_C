#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    // Check password validity rules
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    string special = "!@#$%^&*()_+-=[]{}|;:,.<>?/";
    for (char c : s) {
        if (c >= 'A' && c <= 'Z') hasUpper = true;
        else if (c >= 'a' && c <= 'z') hasLower = true;
        else if (c >= '0' && c <= '9') hasDigit = true;
        else hasSpecial = true;
    }
    int score = 0;
    if (hasUpper) score++;
    if (hasLower) score++;
    if (hasDigit) score++;
    if (hasSpecial) score++;
    if (s.length() >= 8) score++;
    if (score >= 4) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}
