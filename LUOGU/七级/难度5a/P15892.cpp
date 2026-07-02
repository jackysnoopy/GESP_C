#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> h(k);
    for (int i = 0; i < k; i++) cin >> h[i];
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    // prefix_max[i][j] = max height in column j from rows 0..i-1
    vector<vector<int>> pmax(n, vector<int>(m, 0));
    for (int j = 0; j < m; j++) {
        for (int i = 1; i < n; i++) {
            pmax[i][j] = max(pmax[i-1][j], a[i-1][j]);
        }
    }
    sort(h.begin(), h.end());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + k <= m; j++) {
            vector<int> req;
            for (int c = j; c < j + k; c++) req.push_back(pmax[i][c]);
            sort(req.begin(), req.end());
            bool ok = true;
            for (int t = 0; t < k; t++) {
                if (h[t] <= req[t]) { ok = false; break; }
            }
            if (ok) ans++;
        }
    }
    cout << ans << "\n";
    return 0;
}
