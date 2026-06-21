#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> words(n);
    for (int i = 0; i < n; i++) cin >> words[i];
    int ans = 0;
    for (int j = 0; j < m; j++) {
        int cnt[26] = {};
        for (int i = 0; i < n; i++) cnt[words[i][j] - 'a']++;
        int mx = 0;
        for (int c = 0; c < 26; c++) mx = max(mx, cnt[c]);
        ans += n - mx;
    }
    cout << ans << "\n";
    return 0;
}
