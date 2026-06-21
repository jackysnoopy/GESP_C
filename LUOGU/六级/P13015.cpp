#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= i; k++) {
            dp[i] = max(dp[i], dp[i - k] + a[k]);
        }
    }

    cout << dp[n] << "\n";
    return 0;
}
