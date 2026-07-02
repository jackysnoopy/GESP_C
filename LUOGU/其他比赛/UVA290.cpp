#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isPalindrome(const string& s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        l++;
        r--;
    }
    return true;
}

string toBase(long long n, int base) {
    if (n == 0) return "0";
    string result;
    while (n > 0) {
        int digit = n % base;
        if (digit < 10) result += ('0' + digit);
        else result += ('a' + digit - 10);
        n /= base;
    }
    return result;
}

int main() {
    long long n;
    while (cin >> n) {
        vector<int> bases;
        for (int b = 2; b <= 16; b++) {
            string s = toBase(n, b);
            if (isPalindrome(s)) {
                bases.push_back(b);
            }
        }
        if (bases.empty()) {
            cout << "Number " << n << " is not a palindrome." << endl;
        } else {
            cout << "Number " << n << " is palindromic in ";
            for (int i = 0; i < (int)bases.size(); i++) {
                if (i > 0) cout << ", ";
                cout << "base " << bases[i];
            }
            cout << "." << endl;
        }
    }
    return 0;
}
