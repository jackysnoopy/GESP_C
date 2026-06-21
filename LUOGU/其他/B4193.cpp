#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a, b;
    cin >> n >> a >> b;
    string s;
    cin >> s;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '*') continue;
        int j = i;
        while (j < n && s[j] == '.') j++;
        int len = j - i;
        if (len == 1) {
            if (a > 0) { ans++; a--; }
            else if (b > 0) { ans++; b--; }
        } else {
            int start_m = (i % 2 == 0) ? 0 : 1;
            int cnt[2] = {0, 0};
            for (int k = 0; k < len; k++) {
                int need = ((i + k) % 2 == 0) ? 0 : 1;
                if (need == start_m) cnt[0]++;
                else cnt[1]++;
            }
            int use0 = min(a, cnt[0]);
            int use1 = min(b, cnt[1]);
            ans += use0 + use1;
            a -= use0;
            b -= use1;
            if (use0 < cnt[0] && b > 0) {
                int extra = min(b, cnt[0] - use0);
                ans += extra;
                b -= extra;
            }
            if (use1 < cnt[1] && a > 0) {
                int extra = min(a, cnt[1] - use1);
                ans += extra;
                a -= extra;
            }
        }
        i = j - 1;
    }
    cout << ans << "\n";
    return 0;
}
