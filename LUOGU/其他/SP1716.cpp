#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 50001;
const int INF = -1e9;
struct Node { int sum, pre, suf, mx; } tree[MAXN * 4];
int n;
Node merge(Node a, Node b) {
    Node c;
    c.sum = a.sum + b.sum;
    c.pre = max(a.pre, a.sum + b.pre);
    c.suf = max(b.suf, b.sum + a.suf);
    c.mx = max(max(a.mx, b.mx), a.suf + b.pre);
    return c;
}
void build(int p, int l, int r, vector<int>& a) {
    if (l == r) { tree[p] = {a[l], a[l], a[l], a[l]}; return; }
    int mid = (l + r) / 2;
    build(p*2, l, mid, a); build(p*2+1, mid+1, r, a);
    tree[p] = merge(tree[p*2], tree[p*2+1]);
}
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] = {v, v, v, v}; return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = merge(tree[p*2], tree[p*2+1]);
}
Node query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    if (R <= mid) return query(p*2, l, mid, L, R);
    if (L > mid) return query(p*2+1, mid+1, r, L, R);
    return merge(query(p*2, l, mid, L, R), query(p*2+1, mid+1, r, L, R));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n, a);
    int m; cin >> m;
    while (m--) {
        int op, x, y; cin >> op >> x >> y;
        if (op == 0) update(1, 1, n, x, y);
        else cout << query(1, 1, n, x, y).mx << '\n';
    }
    return 0;
}
