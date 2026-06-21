#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) cin >> a[i][j];
    // Simple approach: each row independently choose one element
    // But need to read the actual problem...
    // For now, basic DP
    vector<long long> dp(m, 0);
    for (int j = 0; j < m; j++) dp[j] = a[0][j];
    for (int i = 1; i < n; i++) {
        vector<long long> ndp(m);
        for (int j = 0; j < m; j++) {
            ndp[j] = dp[j] + a[i][j];
            if (j > 0) ndp[j] = max(ndp[j], dp[j-1] + a[i][j]);
            if (j < m-1) ndp[j] = max(ndp[j], dp[j+1] + a[i][j]);
        }
        dp = ndp;
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";
    return 0;
}
