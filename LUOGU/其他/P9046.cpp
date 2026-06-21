#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        string s;
        cin >> n >> s;
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;
        int ones = 0, zeros = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] == 1) ++ones;
            else if (cnt[i] == 0) ++zeros;
        }
        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            if (cnt[i] == 0) {
                if (ones >= 2) { ones -= 2; ans++; }
                else if (ones == 1) { ones--; ans++; }
                else if (zeros >= 2) { zeros -= 2; ans++; }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
