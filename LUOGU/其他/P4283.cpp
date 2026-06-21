#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2, s3;
    int n1, n2, n3;
    cin >> n1 >> s1 >> n2 >> s2 >> n3 >> s3;
    int ans = n1 + n2 + n3;
    for (int i = 0; i <= n1; i++) {
        for (int j = 0; j <= n2; j++) {
            for (int k = 0; k <= n3; k++) {
                int len = max({i, j, k});
                int cost = (n1 - i) + (n2 - j) + (n3 - k) + (len - i) + (len - j) + (len - k);
                bool ok = true;
                for (int t = 0; t < len; t++) {
                    char c = 0;
                    if (t < i && s1[t] != 0) {
                        if (c == 0) c = s1[t];
                        else if (c != s1[t]) { ok = false; break; }
                    }
                    if (t < j && s2[t] != 0) {
                        if (c == 0) c = s2[t];
                        else if (c != s2[t]) { ok = false; break; }
                    }
                    if (t < k && s3[t] != 0) {
                        if (c == 0) c = s3[t];
                        else if (c != s3[t]) { ok = false; break; }
                    }
                }
                if (ok) ans = min(ans, cost);
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
