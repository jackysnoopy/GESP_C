#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int k;
    string s;
    cin >> k >> s;
    int n = s.size();
    if (n % k != 0) { cout << -1 << "\n"; return 0; }
    int block = n / k;
    int ans = 0;
    for (int i = 0; i < block; i++) {
        int cnt[26] = {};
        for (int j = i; j < n; j += block) {
            cnt[s[j] - 'a']++;
        }
        int mx = 0;
        for (int c = 0; c < 26; c++) mx = max(mx, cnt[c]);
        ans += k - mx;
    }
    cout << ans << "\n";
    return 0;
}
