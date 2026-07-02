#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 5005;
int a[MAXN];
int dp[MAXN][MAXN];

int solve(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    int res = solve(l + 1, r); // skip a[l]

    // Try to match a[l] with some a[k] where l < k <= r
    for (int k = l + 1; k <= r; k++) {
        if (a[l] == a[k]) {
            // Remove a[l..k] by having them meet
            // The cards between l and k (exclusive) are removed together
            int mid = solve(l + 1, k - 1);
            int right = solve(k + 1, r);
            res = max(res, mid + right + (k - l + 1));
        }
    }

    return dp[l][r] = res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];

        memset(dp, -1, sizeof(dp));
        cout << solve(0, n - 1) << "\n";
    }

    return 0;
}
