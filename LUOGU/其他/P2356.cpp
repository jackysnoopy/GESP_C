#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> g(n, vector<int>(n));
    vector<long long> rowSum(n, 0), colSum(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
            rowSum[i] += g[i][j];
            colSum[j] += g[i][j];
        }
    }
    long long ans = -1;
    bool hasEmpty = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == 0) {
                hasEmpty = true;
                ans = max(ans, rowSum[i] + colSum[j]);
            }
        }
    }
    if (!hasEmpty) cout << "Bad Game!" << "\n";
    else cout << ans << "\n";
    return 0;
}
