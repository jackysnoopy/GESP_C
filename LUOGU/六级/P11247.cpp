#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m, n, k;
    cin >> m >> n >> k;
    
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    vector<vector<int>> groups(m + 1);
    for (int i = 0; i < n; i++) {
        groups[a[i]].push_back(b[i]);
    }
    
    for (int t = 1; t <= m; t++) {
        sort(groups[t].rbegin(), groups[t].rend());
    }
    
    vector<int> c(m + 1, 0);
    vector<ll> rem(m + 1, 0);
    
    for (int t = 1; t <= m; t++) {
        ll sum = 0;
        for (int val : groups[t]) {
            sum += val;
            c[t]++;
            if (sum >= k) break;
        }
        if (sum < k) {
            cout << -1 << '\n';
            return 0;
        }
        rem[t] = (ll)groups[t].size() - c[t];
    }
    
    ll total = 0;
    int mx = 0;
    for (int t = 1; t <= m; t++) {
        total += c[t];
        mx = max(mx, c[t]);
    }
    
    if (mx <= total - mx + 1) {
        cout << total << '\n';
        return 0;
    }
    
    ll need = (ll)mx - (total - mx + 1);
    ll extra = 0;
    for (int t = 1; t <= m; t++) {
        if (c[t] < mx) extra += rem[t];
    }
    
    if (extra >= need) {
        cout << total + need << '\n';
    } else {
        cout << -1 << '\n';
    }
    
    return 0;
}
