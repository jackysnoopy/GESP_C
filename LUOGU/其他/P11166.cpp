#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
    vector<int> y_vals;
    for (int i = 0; i < n; i++) y_vals.push_back(b[i]);
    sort(y_vals.begin(), y_vals.end());
    y_vals.erase(unique(y_vals.begin(), y_vals.end()), y_vals.end());
    auto check = [&](ll total) -> bool {
        for (int yi = 0; yi < (int)y_vals.size(); yi++) {
            ll Y = y_vals[yi];
            ll X = total - Y;
            if (X < 0) continue;
            vector<pair<int,int>> avail;
            for (int i = 0; i < n; i++) if (b[i] <= Y) avail.push_back({a[i], c[i]});
            sort(avail.begin(), avail.end());
            ll power = X;
            int defeated = 0;
            for (int i = 0; i < (int)avail.size() && power >= 0; i++) {
                if (power >= avail[i].first) { power += avail[i].second; defeated++; if (defeated >= k) break; }
            }
            if (defeated >= k) return true;
        }
        return false;
    };
    ll lo = 0, hi = (ll)2e18;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
    return 0;
}
