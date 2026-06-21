#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        int mx = *max_element(a.begin(), a.end());
        int mn = *min_element(a.begin(), a.end());
        int cnt_mx = 0, cnt_mn = 0;
        for (int x : a) {
            if (x == mx) ++cnt_mx;
            if (x == mn) ++cnt_mn;
        }
        if (mx == mn || m > 0) {
            cout << 0 << '\n';
            continue;
        }
        if (cnt_mx >= 2 || cnt_mn >= 2) {
            cout << mx - mn << '\n';
            continue;
        }
        vector<int> vals;
        for (int x : a) if (x != mx && x != mn) vals.push_back(x);
        if (vals.empty()) {
            cout << mx - mn << '\n';
            continue;
        }
        int mnv = *min_element(vals.begin(), vals.end());
        int mxv = *max_element(vals.begin(), vals.end());
        cout << min(mx - mnv, mxv - mn) << '\n';
    }
    return 0;
}
