#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int n;
ll a[5005];
int digs[5005][8];
int dlen[5005];
vector<ll> vals[5005][8];

void gen_vals(int idx, int k) {
    int d = dlen[idx];
    vector<ll>& res = vals[idx][k];
    res.clear();

    function<void(int, int, ll)> dfs = [&](int pos, int rem, ll v) {
        if (pos == d) {
            if (rem == 0) res.push_back(v);
            return;
        }
        for (int z = 0; z <= rem; z++) {
            ll nv = v;
            for (int i = 0; i < z; i++) nv *= 10;
            nv = nv * 10 + digs[idx][pos];
            dfs(pos + 1, rem - z, nv);
        }
    };

    dfs(0, k, 0);
    sort(res.begin(), res.end());
}

// dp[k] = {min_inserts, min_value} for current row
pair<ll, ll> prev_dp[8];
pair<ll, ll> curr_dp[8];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ll x = a[i];
        vector<int> d;
        if (x == 0) {
            d.push_back(0);
        }
        while (x > 0) {
            d.push_back(x % 10);
            x /= 10;
        }
        reverse(d.begin(), d.end());
        dlen[i] = (int)d.size();
        for (int j = 0; j < dlen[i]; j++) {
            digs[i][j] = d[j];
        }
    }

    // 预处理
    for (int i = 0; i < n; i++) {
        for (int k = 0; k <= 7; k++) {
            gen_vals(i, k);
        }
    }

    // 初始化第0行
    for (int k = 0; k <= 7; k++) {
        if (!vals[0][k].empty()) {
            prev_dp[k] = {k, vals[0][k][0]};
        } else {
            prev_dp[k] = {INF, INF};
        }
    }

    // DP
    for (int i = 1; i < n; i++) {
        for (int k = 0; k <= 7; k++) {
            curr_dp[k] = {INF, INF};
            for (int k2 = 0; k2 <= 7; k2++) {
                if (prev_dp[k2].first == INF) continue;
                ll pv = prev_dp[k2].second;
                auto it = upper_bound(vals[i][k].begin(), vals[i][k].end(), pv);
                if (it != vals[i][k].end()) {
                    ll nt = prev_dp[k2].first + k;
                    ll nv = *it;
                    if (nt < curr_dp[k].first ||
                        (nt == curr_dp[k].first && nv < curr_dp[k].second)) {
                        curr_dp[k] = {nt, nv};
                    }
                }
            }
        }
        for (int k = 0; k <= 7; k++) {
            prev_dp[k] = curr_dp[k];
        }
    }

    ll ans = INF;
    for (int k = 0; k <= 7; k++) {
        ans = min(ans, prev_dp[k].first);
    }
    cout << ans << "\n";

    return 0;
}
