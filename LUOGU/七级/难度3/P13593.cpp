#include <iostream>
#include <string>
using namespace std;
bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}
int main() {
    string s, f;
    getline(cin, s);
    getline(cin, f);
    int i = 0, j = 0;
    bool ok = true;
    while (i < (int)s.size() && j < (int)f.size()) {
        char sc = tolower(s[i]), fc = tolower(f[j]);
        if (sc == fc) { i++; j++; }
        else if (isVowel(f[j])) j++;
        else { ok = false; break; }
    }
    if (ok) {
        while (j < (int)f.size() && isVowel(f[j])) j++;
        if (i < (int)s.size()) ok = false;
        if (j < (int)f.size()) ok = false;
    }
    cout << (ok ? "Same" : "Different") << "\n";
    return 0;
}
