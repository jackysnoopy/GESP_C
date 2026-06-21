#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<long long>> a(n + 3, vector<long long>(n + 3, 0));
    while (m--) {
        int x, y, v;
        cin >> x >> y >> v;
        a[x][y] += v;
    }
    // 2D diff
    vector<vector<long long>> d(n + 3, vector<long long>(n + 3, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            d[i][j] = a[i][j] - a[i-1][j] - a[i][j-1] + a[i-1][j-1];
        }
    }
    long long ans = 0;
    for (int i = 1; i + k - 1 <= n; i++) {
        for (int j = 1; j + k - 1 <= n; j++) {
            d[i][j] += d[i-1][j] + d[i][j-1] - d[i-1][j-1];
            if (d[i][j] != 0) {
                long long val = d[i][j];
                ans += abs(val);
                d[i][j] -= val;
                d[i][j+k] += val;
                d[i+k][j] += val;
                d[i+k][j+k] -= val;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
