#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> diff(n + 2, vector<int>(n + 2, 0));
    while (m--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        diff[x1][y1] += 1;
        diff[x1][y2 + 1] -= 1;
        diff[x2 + 1][y1] -= 1;
        diff[x2 + 1][y2 + 1] += 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            diff[i][j] += diff[i-1][j] + diff[i][j-1] - diff[i-1][j-1];
            cout << diff[i][j] << " \n"[j == n];
        }
    }
    return 0;
}
