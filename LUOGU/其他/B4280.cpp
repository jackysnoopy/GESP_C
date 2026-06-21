#include <iostream>
using namespace std;

const int MAXN = 500005;
const int MAXV = 80;

int dp[MAXN][MAXV + 1];
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i][a[i]] = i;
    }
    int ans = 0;
    for (int v = 2; v <= MAXV; v++) {
        for (int i = 1; i <= n; i++) {
            if (dp[i][v - 1] && dp[i][v - 1] + 1 <= n && dp[dp[i][v - 1] + 1][v - 1]) {
                dp[i][v] = dp[dp[i][v - 1] + 1][v - 1];
                if (v > ans) ans = v;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}
