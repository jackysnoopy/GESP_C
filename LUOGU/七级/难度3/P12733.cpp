#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<ll> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());
    vector<ll> S(n + 1, 0), W(n + 1, 0);
    for (int i = 0; i < n; i++) {
        S[i + 1] = S[i] + d[i];
        W[i + 1] = W[i] + d[i] * i;
    }
    while (q--) {
        ll t;
        cin >> t;
        int lo = 0, hi = n, ans = 0;
        while (lo <= hi) {
            int m = (lo + hi) / 2;
            ll cost = (ll)m * S[m] - W[m];
            if (cost <= t) { ans = m; lo = m + 1; }
            else hi = m - 1;
        }
        cout << ans << "\n";
    }
    return 0;
}
