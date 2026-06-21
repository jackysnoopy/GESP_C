#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int bal = 0, ans = 0;
    for (char c : s) {
        if (c == '(') bal++;
        else bal--;
        if (bal < 0) { ans++; bal = 1; }
    }
    ans += bal / 2;
    cout << ans << "\n";
    return 0;
}
