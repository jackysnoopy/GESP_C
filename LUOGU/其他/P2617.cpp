#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    while (m--) {
        char op; cin >> op;
        if (op == 'C') { int x, y; cin >> x >> y; a[x] = y; }
        else {
            int l, r, k; cin >> l >> r >> k;
            int lo = -1e9, hi = 1e9, ans = 0;
            while (lo <= hi) {
                int mid = (lo + hi) / 2, cnt = 0;
                for (int i = l; i <= r; ++i) if (a[i] <= mid) cnt++;
                if (cnt >= k) { ans = mid; hi = mid - 1; } else lo = mid + 1;
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
