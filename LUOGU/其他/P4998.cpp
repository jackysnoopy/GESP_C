#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
typedef long long ll;
int n, K;
ll a[1000001], ps[1000001];
ll dp[101][1000001];
ll getCost(int l, int r) {
    int m = (l+r)/2;
    ll left = a[m]*(m-l) - (ps[m]-ps[l]);
    ll right = (ps[r+1]-ps[m+1]) - a[m]*(r-m);
    return left + right;
}
void compute(int j, int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l+r)/2;
    int opt = optl;
    dp[j][mid] = LLONG_MAX;
    for (int m = optl; m <= min(mid-1, optr); m++) {
        ll val = dp[j-1][m] + getCost(m, mid-1);
        if (val < dp[j][mid]) { dp[j][mid] = val; opt = m; }
    }
    compute(j, l, mid-1, optl, opt);
    compute(j, mid+1, r, opt, optr);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> K;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a+n);
    ps[0] = 0;
    for (int i = 0; i < n; i++) ps[i+1] = ps[i] + a[i];
    for (int j = 0; j <= K; j++) for (int i = 0; i <= n; i++) dp[j][i] = LLONG_MAX;
    dp[0][0] = 0;
    for (int j = 1; j <= K; j++)
        compute(j, K, n, 0, n);
    cout << dp[K][n] << "\n";
    return 0;
}
