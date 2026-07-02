#include <iostream>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int caseno = 1;

    while (cin >> n >> m) {
        bool h[11][11] = {};
        bool v[11][11] = {};

        for (int i = 0; i < m; i++) {
            char c;
            int a, b;
            cin >> c >> a >> b;
            if (c == 'H') h[a][b] = true;
            else v[b][a] = true;
        }

        if (caseno > 1) cout << "\n\n";
        cout << "Problem #" << caseno << "\n\n";
        caseno++;

        int ans[11] = {};
        for (int sz = 1; sz <= n; sz++) {
            for (int i = 1; i + sz <= n; i++) {
                for (int j = 1; j + sz <= n; j++) {
                    bool ok = true;
                    for (int k = 0; k < sz && ok; k++) {
                        if (!h[i][j + k]) ok = false;
                        if (!h[i + sz][j + k]) ok = false;
                        if (!v[i + k][j]) ok = false;
                        if (!v[i + k][j + sz]) ok = false;
                    }
                    if (ok) ans[sz]++;
                }
            }
        }

        bool found = false;
        for (int sz = 1; sz <= n; sz++) {
            if (ans[sz] > 0) {
                cout << sz << " square(s) of size " << sz << "\n";
                found = true;
            }
        }
        if (!found) cout << "No completed squares can be found.\n";
    }

    return 0;
}
