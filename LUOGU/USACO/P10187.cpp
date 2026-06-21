#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string& s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        if (s.size() == 1) {
            cout << "B\n";
        } else if (isPalindrome(s)) {
            cout << "B\n";
        } else if (s.back() == '0') {
            cout << "E\n";
        } else {
            cout << "B\n";
        }
    }
    return 0;
}
