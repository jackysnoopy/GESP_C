#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> d(4, vector<int>(n + 2, 0));
    while (m--) {
        int l, r, x;
        cin >> l >> r >> x;
        d[x][l]++; d[x][r+1]--;
    }
    vector<int> ans(4, 0);
    for (int i = 1; i <= n; i++) {
        int c[4] = {0};
        for (int x = 1; x <= 3; x++) {
            d[x][i] += d[x][i-1];
            if (d[x][i] > 0) c[x] = 1;
        }
        int sum = c[1] + c[2] + c[3];
        if (sum == 1) {
            for (int x = 1; x <= 3; x++) if (c[x]) ans[x]++;
        }
    }
    cout << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
    return 0;
}
