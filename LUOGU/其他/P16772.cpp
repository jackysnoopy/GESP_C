#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        vector<vector<long long>> c(n, vector<long long>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> c[i][j];
        long long ans = 0;
        // Diagonals where i-j is constant
        for (int d = -(n-1); d < n; d++) {
            long long sum = 0;
            for (int i = 0; i < n; i++) {
                int j = i - d;
                if (j >= 0 && j < n) sum += c[i][j];
            }
            ans = max(ans, sum);
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
