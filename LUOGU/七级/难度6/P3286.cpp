#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
int K, len;
ll L, R, digs[60], pw[60];
ll dp[60][2][3005][3005];
ll dfs(int pos, int tight, ll sumL, ll sumR) {
    if (pos < 0) return sumR;
    ll &res = dp[pos][tight][sumL][sumR];
    if (res != -1) return res;
    res = 0;
    int lim = tight ? digs[pos] : K - 1;
    for (int d = 0; d <= lim; d++) {
        ll nsumL = sumL + d * pw[pos];
        ll nsumR = sumR + d * (pos + 1);
        res += dfs(pos - 1, tight && d == lim, sumL, sumR + d);
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> L >> R >> K;
    auto decompose = [](ll x) {
        vector<int> v;
        while (x) { v.push_back(x % K); x /= K; }
        return v;
    };
    auto calc = [](ll x) -> ll {
        if (x <= 0) return 0;
        vector<int> d;
        while (x) { d.push_back(x % K); x /= K; }
        int n = d.size();
        ll sum = 0;
        for (int i = 0; i < n; i++) sum += d[i];
        ll pos = 0, cost = 0;
        ll pref = 0;
        for (int i = n - 1; i >= 0; i--) {
            pref += d[i];
            if (pref * 2 >= sum) {
                pos = n - 1 - i;
                break;
            }
        }
        for (int i = 0; i < n; i++) {
            cost += (ll)d[i] * abs(i - (int)pos);
        }
        return cost;
    };
    ll ans = 0;
    for (ll x = L; x <= R; x++) {
        ans += calc(x);
    }
    cout << ans << endl;
    return 0;
}