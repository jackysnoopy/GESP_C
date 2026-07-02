#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    vector<vector<int>> bowls(m);
    for (int i = 0; i < m; i++) {
        int ni;
        cin >> ni;
        bowls[i].resize(ni);
        for (int j = 0; j < ni; j++) {
            cin >> bowls[i][j];
        }
        sort(bowls[i].begin(), bowls[i].end());
    }

    vector<long long> results(m, 0);
    for (int u = 0; u < m; u++) {
        for (int v = 0; v < m; v++) {
            if (u == v) continue;

            int nu = bowls[u].size();
            int nv = bowls[v].size();
            int total = nu + nv;
            int k = (total + 1) / 2;

            int i = 0, j = 0, cnt = 0;
            int ans = 0;
            while (cnt < k) {
                if (i < nu && (j >= nv || bowls[u][i] <= bowls[v][j])) {
                    ans = bowls[u][i];
                    i++;
                } else {
                    ans = bowls[v][j];
                    j++;
                }
                cnt++;
            }

            results[u] ^= ((long long)ans + u + v);
        }
    }

    for (int i = 0; i < m; i++) {
        cout << results[i] << "\n";
    }
    return 0;
}
