#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> seg(4 * n);
    for (int i = 0; i < n; i++) seg[n + i] = a[i];
    for (int i = n - 1; i > 0; i--) seg[i] = max(seg[2 * i], seg[2 * i + 1]);
    auto query = [&](int l, int r) {
        int res = 0;
        l += n; r += n;
        while (l <= r) {
            if (l % 2 == 1) res = max(res, seg[l++]);
            if (r % 2 == 0) res = max(res, seg[r--]);
            l /= 2; r /= 2;
        }
        return res;
    };
    auto update = [&](int pos, int val) {
        pos += n;
        seg[pos] = val;
        for (pos /= 2; pos > 0; pos /= 2) seg[pos] = max(seg[2 * pos], seg[2 * pos + 1]);
    };
    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) { int pos, val; cin >> pos >> val; update(pos - 1, val); }
        else { int l, r; cin >> l >> r; cout << query(l - 1, r - 1) << "\n"; }
    }
    return 0;
}
