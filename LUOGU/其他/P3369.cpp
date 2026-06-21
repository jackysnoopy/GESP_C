#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN = 100001;
int ch[MAXN][2], fa[MAXN], sz[MAXN], cnt[MAXN], val[MAXN], tot, root;
void upd(int p) { sz[p] = sz[ch[p][0]] + sz[ch[p][1]] + cnt[p]; }
void rot(int x) {
    int y = fa[x], z = fa[y], d = ch[y][1] == x;
    ch[z][ch[z][1] == y] = x; fa[x] = z;
    ch[y][d] = ch[x][d^1]; fa[ch[x][d^1]] = y;
    ch[x][d^1] = y; fa[y] = x;
    upd(y); upd(x);
}
void splay(int x, int g = 0) {
    while (fa[x] != g) {
        int y = fa[x], z = fa[y];
        if (z != g) ((ch[z][1] == y) ^ (ch[y][1] == x)) ? rot(x) : rot(y);
        rot(x);
    }
    if (!g) root = x;
}
void ins(int v) {
    int x = root, p = 0;
    while (x && val[x] != v) { p = x; x = ch[x][v > val[x]]; }
    if (x) { cnt[x]++; } else {
        x = ++tot; val[x] = v; cnt[x] = sz[x] = 1; fa[x] = p;
        if (p) ch[p][v > val[p]] = x;
    }
    splay(x);
}
void find(int v) {
    int x = root;
    while (x && val[x] != v) x = ch[x][v > val[x]];
    if (x) splay(x);
}
int kth(int k) {
    int x = root;
    while (x) {
        if (ch[x][0] && sz[ch[x][0]] >= k) x = ch[x][0];
        else if (sz[ch[x][0]] + cnt[x] >= k) return val[x];
        else { k -= sz[ch[x][0]] + cnt[x]; x = ch[x][1]; }
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; scanf("%d", &n);
    ins(-2147483647); ins(2147483647);
    while (n--) {
        int op, x; scanf("%d%d", &op, &x);
        if (op == 1) ins(x);
        else if (op == 2) { find(x); if (val[root] == x) { cnt[root]--; upd(root); } }
        else if (op == 3) { find(x); printf("%d\n", sz[ch[root][0]]); }
        else if (op == 4) printf("%d\n", kth(x + 1));
        else if (op == 5) { find(x); printf("%d\n", val[root] != x ? val[root] : val[ch[root][0]]); }
        else { find(x); printf("%d\n", val[root] != x ? val[root] : val[ch[root][1]]); }
    }
    return 0;
}
