#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    // 将数字修改为最大的可能
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] == '0' || s[i] == '6' || s[i] == '8') {
            s[i] = '9';
        }
    }

    cout << s << "\n";

    return 0;
}
