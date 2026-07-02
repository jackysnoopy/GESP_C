#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAXN = 200005;
const int LOG = 17;
int trie[MAXN * LOG][2], cnt[MAXN * LOG], root[MAXN], tot;
void insert(int &rt, int prev, int val) {
    rt = ++tot;
    int p = rt, q = prev;
    for (int i = LOG - 1; i >= 0; i--) {
        int b = (val >> i) & 1;
        trie[p][b] = ++tot;
        trie[p][b^1] = trie[q][b^1];
        p = trie[p][b]; q = trie[q][b^1];
        cnt[p] = cnt[trie[rt][b]] + 1;
    }
}
int query(int l, int r, int b, int x) {
    int p = root[r], q = root[l-1];
    int res = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        int want = ((b >> i) ^ 1);
        int xp = (x >> i) & 1;
        int need = (want ^ xp);
        if (cnt[trie[p][need]] - cnt[trie[q][need]] > 0) {
            res |= (1 << i);
            p = trie[p][need]; q = trie[q][need];
        } else {
            p = trie[p][need^1]; q = trie[q][need^1];
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    root[0] = 0; tot = 0;
    for (int i = 1; i <= n; i++) {
        int a; cin >> a;
        insert(root[i], root[i-1], a);
    }
    for (int i = 0; i < m; i++) {
        int b, x, l, r;
        cin >> b >> x >> l >> r;
        cout << query(l, r, b, x) << "\n";
    }
    return 0;
}