#include <iostream>
#include <cstring>
using namespace std;

const int MAXN = 505;
long long dp[MAXN][MAXN];
int a[MAXN];
int n;

long long solve(int l, int r) {
    if (l > r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return dp[l][r] = a[l];
    long long pickL = a[l] - solve(l + 1, r);
    long long pickR = a[r] - solve(l, r - 1);
    return dp[l][r] = max(pickL, pickR);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        memset(dp, -1, sizeof(dp));
        long long result = solve(0, n - 1);
        if (result > 0) cout << "First\n";
        else if (result < 0) cout << "Second\n";
        else cout << "Tie\n";
    }
    return 0;
}
