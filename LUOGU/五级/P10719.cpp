#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) cin >> grid[i];
    vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pref[i][j] = pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1] + (grid[i-1][j-1] == '1');
        }
    }
    auto query = [&](int r1, int c1, int r2, int c2) {
        return pref[r2][c2] - pref[r1-1][c2] - pref[r2][c1-1] + pref[r1-1][c1-1];
    };
    int ans = INT_MAX;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            for (int c1 = 1; c1 <= m; c1++) {
                for (int c2 = c1; c2 <= m; c2++) {
                    if (query(r1, c1, r2, c2) >= k) {
                        ans = min(ans, (r2 - r1 + 1) * (c2 - c1 + 1));
                    }
                }
            }
        }
    }
    cout << (ans == INT_MAX ? 0 : ans) << "\n";
    return 0;
}
