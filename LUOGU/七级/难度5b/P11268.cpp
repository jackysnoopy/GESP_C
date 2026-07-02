#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n), b(n);
    long long base = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        base += b[i];
    }

    vector<pair<long long, long long>> coupons(m);
    for (int i = 0; i < m; i++) {
        cin >> coupons[i].first >> coupons[i].second;
    }

    sort(coupons.begin(), coupons.end(), [](const pair<long long, long long>& x, const pair<long long, long long>& y) {
        return x.second > y.second;
    });

    vector<int> ord(n);
    for (int i = 0; i < n; i++) ord[i] = i;
    sort(ord.begin(), ord.end(), [&](int i, int j) { return a[i] < a[j]; });

    const long long INF = 4e18;
    int sz = 1;
    while (sz < n) sz *= 2;
    vector<long long> tree(2 * sz, INF);

    for (int i = 0; i < n; i++) {
        tree[sz + i] = a[ord[i]] - b[ord[i]];
    }
    for (int i = sz - 1; i >= 1; i--) {
        tree[i] = min(tree[2 * i], tree[2 * i + 1]);
    }

    auto update = [&](int pos, long long val) {
        pos += sz;
        tree[pos] = val;
        for (pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos] = min(tree[2 * pos], tree[2 * pos + 1]);
        }
    };

    auto queryMin = [&](int l, int r) -> long long {
        long long res = INF;
        for (l += sz, r += sz; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) res = min(res, tree[l++]);
            if (!(r & 1)) res = min(res, tree[r--]);
        }
        return res;
    };

    long long savings = 0;
    for (int ci = 0; ci < m; ci++) {
        long long w = coupons[ci].first;
        long long v = coupons[ci].second;

        int lo = 0, hi = n - 1, pos = n;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (a[ord[mid]] >= w) {
                pos = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        if (pos >= n) continue;

        long long mn = queryMin(pos, n - 1);
        if (mn >= INF || v <= mn) continue;

        savings += v - mn;

        int l = pos, r = n - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (queryMin(pos, mid) <= mn) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        update(l, INF);
    }

    cout << base - savings << "\n";
    return 0;
}
