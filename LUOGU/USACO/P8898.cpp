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
        int N, K;
        string s;
        cin >> N >> K >> s;
        string ans(N, '.');
        int needG = 0, needH = 0;
        for (char c : s) {
            if (c == 'G') ++needG;
            else ++needH;
        }
        int i = 0;
        while (i < N && needG > 0) {
            if (s[i] == 'G') {
                int j = min(N - 1, i + K);
                ans[j] = 'G';
                needG--;
                i = j + 1;
                continue;
            }
            ++i;
        }
        i = 0;
        while (i < N && needH > 0) {
            if (s[i] == 'H') {
                int j = min(N - 1, i + K);
                if (ans[j] == 'G') j--;
                ans[j] = 'H';
                needH--;
                i = j + 1;
                continue;
            }
            ++i;
        }
        cout << count(ans.begin(), ans.end(), 'G') + count(ans.begin(), ans.end(), 'H') << '\n' << ans << '\n';
    }
    return 0;
}
