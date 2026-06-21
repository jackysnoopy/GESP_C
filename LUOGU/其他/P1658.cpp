#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x, n;
    cin >> x >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) cin >> c[i];
    sort(c.begin(), c.end());
    if (c[0] != 1) { cout << -1 << "\n"; return 0; }
    for (int i = 0; i <= x; i++) dp[i] = 1e9;
    dp[0] = 0;
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n && c[j] <= i; j++) {
            if (dp[i - c[j]] + 1 < dp[i]) dp[i] = dp[i - c[j]] + 1;
        }
    }
    cout << (dp[x] >= 1e9 ? -1 : dp[x]) << "\n";
    return 0;
}
