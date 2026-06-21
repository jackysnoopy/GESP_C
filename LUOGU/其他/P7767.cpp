#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans = 0;
    char cur = 'A';
    for (int i = 0; i < n; i++) {
        if (s[i] != cur) {
            ans++;
            cur = (cur == 'A') ? 'B' : 'A';
        }
    }
    cout << ans << "\n";
    return 0;
}
