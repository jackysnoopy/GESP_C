#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 40000;
const double eps = 1e-9;
struct Line { double k, b; int id; };
Line tree[MAXN * 4];
int cnt;
void insert(int node, int l, int r, Line line) {
    if (!tree[node].id) { tree[node] = line; return; }
    int mid = (l + r) / 2;
    if (line.k * mid + line.b > tree[node].k * mid + tree[node].b) swap(tree[node], line);
    if (l == r) return;
    if (line.k > tree[node].k) insert(node * 2, mid + 1, r, line);
    else insert(node * 2, l, mid, line);
}
int query(int node, int l, int r, int x) {
    if (l == r) return tree[node].id;
    int mid = (l + r) / 2;
    int res = tree[node].id;
    if (x <= mid) {
        int t = query(node * 2, l, mid, x);
        if (!res || (t && tree[node * 2].k * x + tree[node * 2].b > tree[res].k * x + tree[res].b)) res = t;
    } else {
        int t = query(node * 2 + 1, mid + 1, r, x);
        if (!res || (t && tree[node * 2 + 1].k * x + tree[node * 2 + 1].b > tree[res].k * x + tree[res].b)) res = t;
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, lastans = 0;
    cin >> n;
    cnt = 0;
    while (n--) {
        int op; cin >> op;
        if (op == 0) {
            int k; cin >> k;
            k = (k + lastans - 1) % 39989 + 1;
            int r = query(1, 1, 39989, k);
            cout << r << "\n";
            lastans = r;
        } else {
            double x0, y0, x1, y1;
            int ix0, iy0, ix1, iy1;
            cin >> ix0 >> iy0 >> ix1 >> iy1;
            ix0 = (ix0 + lastans - 1) % 39989 + 1;
            iy0 = (iy0 + lastans - 1) % 1000000000 + 1;
            ix1 = (ix1 + lastans - 1) % 39989 + 1;
            iy1 = (iy1 + lastans - 1) % 1000000000 + 1;
            if (ix0 == ix1) {
                int id = ++cnt;
                double b = max(iy0, iy1);
                insert(1, 1, 39989, {0, b, id});
            } else {
                if (ix0 > ix1) { swap(ix0, ix1); swap(iy0, iy1); }
                int id = ++cnt;
                double k = (double)(iy1 - iy0) / (ix1 - ix0);
                double b = iy0 - k * ix0;
                insert(1, 1, 39989, {k, b, id});
            }
        }
    }
    return 0;
}