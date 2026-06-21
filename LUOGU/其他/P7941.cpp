#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        string E;
        cin >> n >> E;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                string sub = E.substr(i, j - i);
                bool valid = true;
                int ops = 0, nums = 0;
                for (char c : sub) {
                    if (c == '0' || c == '1') nums++;
                    else if (c == '&' || c == '|' || c == '?') ops++;
                    else { valid = false; break; }
                }
                if (!valid || nums != ops + 1) continue;
                ans++;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
