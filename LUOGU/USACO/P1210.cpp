#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string text, line;
    while (getline(cin, line)) text += line + "\n";
    
    string letters;
    vector<int> pos;
    for (int i = 0; i < (int)text.size(); i++) {
        if (isalpha(text[i])) {
            letters += tolower(text[i]);
            pos.push_back(i);
        }
    }
    
    int n = letters.size(), best_len = 0, best_l = 0, best_r = 0;
    for (int c = 0; c < n; c++) {
        int l = c, r = c;
        while (l >= 0 && r < n && letters[l] == letters[r]) { l--; r++; }
        int len = r - l - 1;
        if (len > best_len) { best_len = len; best_l = l + 1; best_r = r - 1; }
        
        l = c; r = c + 1;
        while (l >= 0 && r < n && letters[l] == letters[r]) { l--; r++; }
        len = r - l - 1;
        if (len > best_len) { best_len = len; best_l = l + 1; best_r = r - 1; }
    }
    
    cout << best_len << "\n";
    for (int i = pos[best_l]; i <= pos[best_r]; i++)
        cout << text[i];
    return 0;
}