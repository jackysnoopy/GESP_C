#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        bool hasLower = false, hasUpper = false, hasDigit = false;
        int convertible = 0;
        for (char c : s) {
            if (c >= 'a' && c <= 'z') hasLower = true;
            else if (c >= 'A' && c <= 'Z') hasUpper = true;
            else if (c >= '0' && c <= '9') hasDigit = true;
            if (c == 'O' || c == 'o' || c == '0') convertible++;
        }
        int need = 0;
        if (!hasLower) need++;
        if (!hasUpper) need++;
        if (!hasDigit) need++;
        if (need > convertible) cout << -1 << "\n";
        else cout << need << "\n";
    }
    return 0;
}
