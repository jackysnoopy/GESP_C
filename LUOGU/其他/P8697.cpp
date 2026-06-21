#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    cin >> s >> t;
    int j = 0;
    for (int i = 0; i < (int)s.size() && j < (int)t.size(); i++) {
        if (s[i] == t[j]) j++;
    }
    cout << j << "\n";
    return 0;
}
