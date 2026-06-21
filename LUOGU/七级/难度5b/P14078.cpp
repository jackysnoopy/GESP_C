#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// BIT (Fenwick Tree) for range max query
struct BIT {
    int n;
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    void update(int i, int val) {
        for (; i <= n; i += i & (-i))
            tree[i] = max(tree[i], val);
    }
    int query(int i) {
        int res = 0;
        for (; i > 0; i -= i & (-i))
            res = max(res, tree[i]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> coins(n); // (t, x)
    vector<long long> xs(n);
    for (int i = 0; i < n; i++) {
        long long x, t;
        cin >> x >> t;
        coins[i] = {t, x};
        xs[i] = x;
    }

    // Coordinate compression for x
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    auto getX = [&](long long x) {
        return (int)(lower_bound(xs.begin(), xs.end(), x) - xs.begin()) + 1;
    };

    // Sort by (t - x), so that when processing coin i,
    // all coins j with (t_j - x_j) <= (t_i - x_i) are already processed
    sort(coins.begin(), coins.end(), [](const pair<long long,long long>& a, const pair<long long,long long>& b) {
        long long da = a.first - a.second;
        long long db = b.first - b.second;
        if (da != db) return da < db;
        return a.second < b.second; // tie-break by x
    });

    BIT bit(xs.size());
    int ans = 0;
    for (int i = 0; i < n; i++) {
        long long ti = coins[i].first, xi = coins[i].second;
        if (xi > ti) continue; // can't reach from origin
        int pos = getX(xi);
        int best = bit.query(pos); // max dp[j] with x_j <= x_i
        int dpi = best + 1;
        bit.update(pos, dpi);
        ans = max(ans, dpi);
    }
    cout << ans << "\n";
    return 0;
}
