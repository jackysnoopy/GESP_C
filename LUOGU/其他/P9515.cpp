#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    // Simple string transformation
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') c = c - 'A' + 'a';
    }
    cout << s << "\n";
    return 0;
}
