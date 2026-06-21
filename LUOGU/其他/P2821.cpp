#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string k;
    cin >> k;
    if (k == "1") { cout << "There is no such number!\n"; return 0; }
    long long val = 0;
    for (char c : k) val = val * 10 + (c - '0');
    if (val == 1) { cout << "There is no such number!\n"; return 0; }
    string res = "";
    for (int d = 9; d >= 2; d--) {
        while (val % d == 0) {
            res += char('0' + d);
            val /= d;
        }
    }
    if (val != 1) { cout << "There is no such number!\n"; return 0; }
    reverse(res.begin(), res.end());
    cout << res << "\n";
    return 0;
}
