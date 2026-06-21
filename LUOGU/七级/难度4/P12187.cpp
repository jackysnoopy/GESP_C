#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int i, ll v) {
        for (i++; i <= n; i += i & -i) bit[i] += v;
    }
    ll sum(int i) {
        if (i < 0) return 0;
        ll s = 0;
        for (i++; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
    int lower_bound(ll v) {
        int pos = 0;
        ll acc = 0;
        int pw = 1;
        while (pw <= n) pw <<= 1;
        for (; pw; pw >>= 1) {
            if (pos + pw <= n && acc + bit[pos + pw] < v) {
                pos += pw;
                acc += bit[pos];
            }
        }
        return pos;
    }
};

int main() {
    int n;
    ll m, o;
    scanf("%d %lld %lld", &n, &m, &o);

    vector<ll> a(n), b(n), c(n);
    vector<ll> prices;
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
        prices.push_back(a[i]);
    }

    sort(prices.begin(), prices.end());
    prices.erase(unique(prices.begin(), prices.end()), prices.end());
    int P = prices.size();

    Fenwick cnt(P), sm(P);
    ll total = 0;
    ll ans = LLONG_MAX;

    for (int i = 0; i < n; i++) {
        int idx = (int)(lower_bound(prices.begin(), prices.end(), a[i]) - prices.begin());
        cnt.add(idx, b[i]);
        sm.add(idx, b[i] * a[i]);
        total += b[i];

        if (total >= m) {
            int pos = cnt.lower_bound(m);
            ll cnt_before = cnt.sum(pos - 1);
            ll sum_before = sm.sum(pos - 1);
            ll need = m - cnt_before;
            ll cost = sum_before + need * prices[pos];
            ans = min(ans, o * c[i] + cost);
        }
    }

    printf("%lld\n", ans == LLONG_MAX ? -1LL : ans);
    return 0;
}
