#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            grid[i][j] = s[j] - 'a';
        }
    }

    vector<int> c(26);
    for (int i = 0; i < 26; i++) cin >> c[i];

    long long ans = 0;

    for (int x1 = 0; x1 < m; x1++) {
        for (int x2 = x1 + 1; x2 < m; x2++) {
            for (int y1 = 0; y1 < n; y1++) {
                long long sum = 0;
                for (int x = x1; x <= x2; x++) {
                    sum += c[grid[y1][x]];
                }
                for (int y2 = y1; y2 < n; y2++) {
                    sum += c[grid[y2][x1]];
                    ans = max(ans, sum);
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
