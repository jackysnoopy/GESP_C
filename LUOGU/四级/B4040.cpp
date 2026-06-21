#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<string> g(n);
        for (int i = 0; i < n; i++) cin >> g[i];
        bool found = false;
        for (int i = 0; i + 3 < n && !found; i++) {
            for (int j = 0; j + 3 < m && !found; j++) {
                bool ok = true;
                for (int r = 0; r < 4 && ok; r++) {
                    for (int c = 0; c < 4 && ok; c++) {
                        if (r == 0 || r == 3) {
                            if (g[i + r][j + c] != '0') ok = false;
                        } else {
                            if (c == 0 || c == 3) {
                                if (g[i + r][j + c] != '0') ok = false;
                            } else {
                                if (g[i + r][j + c] != '1') ok = false;
                            }
                        }
                    }
                }
                if (ok) found = true;
            }
        }
        cout << (found ? "Yes\n" : "No\n");
    }
    return 0;
}
