#include <iostream>
#include <string>
using namespace std;

char mirrorChar(char c) {
    switch (c) {
        case 'A': return 'A';
        case 'E': return '3';
        case 'H': return 'H';
        case 'I': return 'I';
        case 'J': return 'L';
        case 'L': return 'J';
        case 'M': return 'M';
        case 'O': return 'O';
        case 'S': return '2';
        case 'T': return 'T';
        case 'U': return 'U';
        case 'V': return 'V';
        case 'W': return 'W';
        case 'X': return 'X';
        case 'Y': return 'Y';
        case 'Z': return '5';
        case '1': return '1';
        case '2': return 'S';
        case '3': return 'E';
        case '5': return 'Z';
        case '8': return '8';
        default: return ' ';
    }
}

bool isPalindrome(const string& s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

bool isMirrored(const string& s) {
    int n = s.size();
    for (int i = 0; i <= n / 2; i++) {
        if (mirrorChar(s[n - 1 - i]) != s[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    bool first = true;
    while (cin >> s) {
        if (!first) cout << "\n";
        first = false;

        bool p = isPalindrome(s);
        bool m = isMirrored(s);

        cout << s << " -- ";
        if (p && m) cout << "is a mirrored palindrome.\n";
        else if (p) cout << "is a palindrome.\n";
        else if (m) cout << "is a mirrored string.\n";
        else cout << "is not a palindrome.\n";
    }

    return 0;
}
