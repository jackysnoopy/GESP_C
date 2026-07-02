#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

bool isPalindrome(const string& s, int l, int r) {
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}

int main() {
    string line;
    while (cin >> line) {
        if (line == "END") break;
        set<string> pals;
        int n = line.size();
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                if (isPalindrome(line, i, j)) {
                    string sub = line.substr(i, j - i + 1);
                    if (sub.size() >= 2) {
                        pals.insert(sub);
                    }
                }
            }
        }
        cout << "The string '" << line << "' contains " << pals.size() << " palindromes." << endl;
    }
    return 0;
}
