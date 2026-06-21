#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, t;
    cin >> s >> t;
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != t[i]) {
            s[i] = t[i];
            s[i+1] = (s[i+1] == '*') ? 'o' : '*';
            ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
