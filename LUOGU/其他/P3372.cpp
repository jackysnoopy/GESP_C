#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 100001;
long long tree[MAXN * 4], tag[MAXN * 4];
int n;
void pushup(int p) { tree[p] = tree[p*2] + tree[p*2+1]; }
void pushdown(int p, int l, int r) {
    if (tag[p]) {
        int mid = (l + r) / 2;
        tree[p*2] += tag[p] * (mid - l + 1); tag[p*2] += tag[p];
        tree[p*2+1] += tag[p] * (r - mid); tag[p*2+1] += tag[p];
        tag[p] = 0;
    }
}
void build(int p, int l, int r, vector<int>& a) {
    tag[p] = 0;
    if (l == r) { tree[p] = a[l]; return; }
    int mid = (l + r) / 2;
    build(p*2, l, mid, a); build(p*2+1, mid+1, r, a);
    pushup(p);
}
void update(int p, int l, int r, int L, int R, long long v) {
    if (L <= l && r <= R) { tree[p] += v * (r - l + 1); tag[p] += v; return; }
    pushdown(p, l, r);
    int mid = (l + r) / 2;
    if (L <= mid) update(p*2, l, mid, L, R, v);
    if (R > mid) update(p*2+1, mid+1, r, L, R, v);
    pushup(p);
}
long long query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    pushdown(p, l, r);
    int mid = (l + r) / 2;
    long long res = 0;
    if (L <= mid) res += query(p*2, l, mid, L, R);
    if (R > mid) res += query(p*2+1, mid+1, r, L, R);
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    build(1, 1, n, a);
    while (m--) {
        int op; cin >> op;
        if (op == 1) { int l, r; long long k; cin >> l >> r >> k; update(1, 1, n, l, r, k); }
        else { int l, r; cin >> l >> r; cout << query(1, 1, n, l, r) << '\n'; }
    }
    return 0;
}
