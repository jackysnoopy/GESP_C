#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 500001;
const int INF = 1e9;
int tree[MAXN * 4];
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] = min(tree[p], v); return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = min(tree[p*2], tree[p*2+1]);
}
int query(int p, int l, int r, int L, int R) {
    if (L > R) return INF;
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2, res = INF;
    if (L <= mid) res = min(res, query(p*2, l, mid, L, R));
    if (R > mid) res = min(res, query(p*2+1, mid+1, r, L, R));
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> tx(n + m + 1), ty(n + m + 1), top(n + m + 1), ans(m + 1, INF);
    for (int i = 1; i <= n; ++i) { cin >> tx[i] >> ty[i]; top[i] = 0; }
    int cnt = n;
    for (int i = 1; i <= m; ++i) {
        int op; cin >> op;
        if (op == 1) { cnt++; cin >> tx[cnt] >> ty[cnt]; top[cnt] = 1; }
        else { cnt++; cin >> tx[cnt] >> ty[cnt]; top[cnt] = 2; }
    }
    int mx = *max_element(tx.begin() + 1, tx.begin() + cnt + 1);
    for (int dir = 0; dir < 4; ++dir) {
        for (int i = 0; i <= mx * 4 + 10; ++i) tree[i] = INF;
        vector<int> ord(cnt);
        for (int i = 1; i <= cnt; ++i) ord[i - 1] = i;
        if (dir == 0) sort(ord.begin(), ord.end(), [&](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); });
        else if (dir == 1) { for (int i = 1; i <= cnt; ++i) ty[i] = -ty[i]; sort(ord.begin(), ord.end(), [&](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        else if (dir == 2) { for (int i = 1; i <= cnt; ++i) tx[i] = -tx[i]; sort(ord.begin(), ord.end(), [&](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        else { for (int i = 1; i <= cnt; ++i) { tx[i] = -tx[i]; ty[i] = -ty[i]; } sort(ord.begin(), ord.end(), [&](int a, int b) { return tx[a] < tx[b] || (tx[a] == tx[b] && ty[a] < ty[b]); }); }
        for (int i : ord) {
            if (top[i] == 0) { update(1, 0, mx, ty[i], tx[i] + ty[i]); }
            else if (top[i] == 2) {
                int d = query(1, 0, mx, 0, ty[i]);
                if (d < INF) ans[i - n] = min(ans[i - n], tx[i] + ty[i] - d);
            }
        }
        for (int i = 1; i <= cnt; ++i) { if (dir & 1) ty[i] = -ty[i]; else tx[i] = -tx[i]; }
    }
    for (int i = 1; i <= m; ++i) if (ans[i] < INF) cout << ans[i] << '\n';
    return 0;
}
