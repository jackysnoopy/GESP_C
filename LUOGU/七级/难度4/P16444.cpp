#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<string> s(n);
        for (int i = 0; i < n; i++) cin >> s[i];

        vector<string> result = s;

        for (int j = 0; j < m; j++) {
            char prev = '0';
            for (int i = 0; i < n; i++) {
                if (s[i][j] == '?') {
                    result[i][j] = prev;
                } else {
                    prev = s[i][j];
                }
            }
        }

        bool valid = true;
        for (int i = 0; i < n - 1; i++) {
            int diff = 0;
            for (int j = 0; j < m; j++) {
                if (result[i][j] != result[i + 1][j]) diff++;
            }
            if (diff > 1) {
                valid = false;
                break;
            }
        }

        if (valid) {
            cout << "Yes\n";
            for (int i = 0; i < n; i++) cout << result[i] << "\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
