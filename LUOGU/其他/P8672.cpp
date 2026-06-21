#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();
    int cnt[3] = {0, 0, 0};
    for (char c : s) {
        if (c == 'A') cnt[0]++;
        else if (c == 'B') cnt[1]++;
        else cnt[2]++;
    }
    int ans = n;
    char order[6][3] = {{'A','B','T'},{'A','T','B'},{'B','A','T'},{'B','T','A'},{'T','A','B'},{'T','B','A'}};
    for (auto &ord : order) {
        int cur = 0, pos = 0;
        for (int k = 0; k < 3; ++k) {
            char ch = ord[k];
            for (int j = 0; j < (k == 0 ? cnt[0] : (k == 1 ? cnt[1] : cnt[2])); ++j) {
                if (s[pos] != ch) ++cur;
                ++pos;
            }
        }
        ans = min(ans, cur / 2);
    }
    cout << ans << '\n';
    return 0;
}
