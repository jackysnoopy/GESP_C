#include <iostream>
#include <string>
#include <vector>
using namespace std;

string caesarDecrypt(const string& s, int k) {
    string result = s;
    for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = 'A' + (c - 'A' - k + 26) % 26;
        } else {
            c = 'a' + (c - 'a' - k + 26) % 26;
        }
    }
    return result;
}

int query(const string& guess) {
    cout << guess << endl;
    int resp;
    cin >> resp;
    if (resp == -1) {
        exit(0);
    }
    return resp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        string T;
        cin >> T;
        int len = T.length();
        string ans(len, ' ');
        int totalCorrect = 0;
        for (int k = 0; k < 52 && totalCorrect < len; k++) {
            string guess = caesarDecrypt(T, k);
            int matches = query(guess);
            if (matches == len) {
                totalCorrect = len;
                break;
            }
            totalCorrect = matches;
        }
    }
    return 0;
}
