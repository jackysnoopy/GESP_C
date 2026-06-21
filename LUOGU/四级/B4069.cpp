#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<string> s(n);
        bool ok = true;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            for (int j = 1; j < (int)s[i].size(); j++) {
                if (s[i][j] < s[i][j - 1]) ok = false;
            }
        }
        if (!ok) {
            cout << "0\n";
            continue;
        }
        sort(s.begin(), s.end(), [](const string &a, const string &b) {
            if (a[0] != b[0]) return a[0] < b[0];
            if (a.back() != b.back()) return a.back() < b.back();
            return a < b;
        });
        string t;
        for (const string &str : s) t += str;
        ok = true;
        for (int i = 1; i < (int)t.size(); i++) {
            if (t[i] < t[i - 1]) {
                ok = false;
                break;
            }
        }
        cout << (ok ? "1\n" : "0\n");
    }
    return 0;
}
