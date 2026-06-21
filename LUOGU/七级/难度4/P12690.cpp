#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int ans = 0;
    int a_count = 0, b_count = 0;

    for (char c : s) {
        if (c == 'A') a_count++;
        else if (c == 'B') {
            if (a_count > 0) {
                a_count--;
                ans++;
            } else {
                b_count++;
            }
        } else {
            if (b_count > 0) {
                b_count--;
                ans++;
            } else if (a_count > 0) {
                a_count--;
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
