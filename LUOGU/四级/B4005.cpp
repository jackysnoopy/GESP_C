#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++) cin >> g[i];
    vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pre[i][j] = pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1] + (g[i - 1][j - 1] == '1');
        }
    }
    int ans = 0;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int c1 = 1; c1 <= m; c1++) {
            for (int r2 = r1; r2 <= n; r2++) {
                for (int c2 = c1; c2 <= m; c2++) {
                    int area = (r2 - r1 + 1) * (c2 - c1 + 1);
                    if (area % 2 != 0) continue;
                    int cnt1 = pre[r2][c2] - pre[r1 - 1][c2] - pre[r2][c1 - 1] + pre[r1 - 1][c1 - 1];
                    if (cnt1 * 2 == area) {
                        if (area > ans) ans = area;
                    }
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
