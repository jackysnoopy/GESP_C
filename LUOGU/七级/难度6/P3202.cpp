#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int m;
int n, d;
vector<long long> h;

long long solve() {
    cin >> n >> d;
    h.resize(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    if (n <= 1) return 0;
    long long lo = 0, hi = 0;
    for (int i = 0; i < n; i++) hi = max(hi, h[i]);
    hi = hi * n;
    long long ans = -1;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        vector<long long> dp(n, -1);
        dp[0] = mid;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] < 0) continue;
                long long diff = abs(h[i] - h[j]);
                long long cost = max(0LL, diff - d);
                if (cost <= dp[j]) {
                    long long rem = dp[j] - cost;
                    if (rem > dp[i]) dp[i] = rem;
                }
            }
        }
        if (dp[n - 1] >= 0) { ans = mid; hi = mid - 1; }
        else lo = mid + 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m;
    while (m--) {
        long long r = solve();
        if (r < 0) cout << "impossible\n";
        else cout << r << "\n";
    }
    return 0;
}
