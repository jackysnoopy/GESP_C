#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; ll w;
    cin >> n >> w;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    auto cost = [&](ll c) -> ll {
        ll total = c * w;
        for (int k = 0; k < n; k++)
            total += max(0LL, a[k] - c - k);
        return total;
    };
    ll lo = 0, hi = a[n - 1];
    while (hi - lo > 3) {
        ll m1 = lo + (hi - lo) / 3;
        ll m2 = hi - (hi - lo) / 3;
        if (cost(m1) < cost(m2)) hi = m2;
        else lo = m1;
    }
    ll ans = cost(lo);
    for (ll c = lo + 1; c <= hi; c++) ans = min(ans, cost(c));
    cout << ans << "\n";
    return 0;
}
