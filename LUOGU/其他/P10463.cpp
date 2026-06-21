#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 500001;
int tree[MAXN * 4], n;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
void build(int p, int l, int r, vector<int>& a) {
    if (l == r) { tree[p] = a[l]; return; }
    int mid = (l + r) / 2;
    build(p*2, l, mid, a); build(p*2+1, mid+1, r, a);
    tree[p] = gcd(tree[p*2], tree[p*2+1]);
}
void update(int p, int l, int r, int pos, int v) {
    if (l == r) { tree[p] += v; return; }
    int mid = (l + r) / 2;
    if (pos <= mid) update(p*2, l, mid, pos, v);
    else update(p*2+1, mid+1, r, pos, v);
    tree[p] = gcd(tree[p*2], tree[p*2+1]);
}
int query(int p, int l, int r, int L, int R) {
    if (L <= l && r <= R) return tree[p];
    int mid = (l + r) / 2;
    if (R <= mid) return query(p*2, l, mid, L, R);
    if (L > mid) return query(p*2+1, mid+1, r, L, R);
    return gcd(query(p*2, l, mid, L, R), query(p*2+1, mid+1, r, L, R));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> n >> m;
    vector<int> a(n + 1), d(n + 1);
    for (int i = 1; i <= n; ++i) { cin >> a[i]; d[i] = a[i] - a[i-1]; }
    build(1, 1, n, d);
    while (m--) {
        char op; int l, r, v;
        cin >> op >> l >> r;
        if (op == 'C') {
            cin >> v;
            update(1, 1, n, l, v);
            if (r + 1 <= n) update(1, 1, n, r + 1, -v);
        } else {
            int g = query(1, 1, n, l + 1, r);
            cout << abs(gcd(a[l], g)) << '\n';
        }
    }
    return 0;
}
