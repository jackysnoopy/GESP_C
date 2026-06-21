#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, K, L; cin >> n >> K >> L;
    vector<double> dp(K + 1, 0);
    dp[0] = 1.0;
    int skip = 0;
    for (int i = 0; i < n; ++i) {
        int a; double p; int r;
        cin >> a >> p >> r;
        if (a == -1) { skip++; continue; }
        for (int j = min(K, i - skip); j >= 0; --j) {
            if (dp[j] <= 0) continue;
            double nv = dp[j] * p;
            int nj = min(K, j + r);
            dp[nj] = max(dp[nj], nv);
        }
    }
    double ans = 0;
    for (int j = L; j <= K; ++j) ans = max(ans, dp[j]);
    printf("%.6f\n", ans);
    return 0;
}
