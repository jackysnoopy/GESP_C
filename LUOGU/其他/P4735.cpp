#include <iostream>
#include <vector>
using namespace std;
const int MAXB = 30;
int ch[6000001][2], cnt[6000001], tot;
int root[500001];
void insert(int &p, int q, int v) {
    p = ++tot;
    int cur = p, qcur = q;
    for (int i = MAXB; i >= 0; --i) {
        int d = (v >> i) & 1;
        ch[cur][d] = ++tot; ch[cur][d^1] = ch[qcur][d^1];
        cur = ch[cur][d]; qcur = ch[qcur][d];
        cnt[cur] = cnt[qcur] + 1;
    }
}
int query(int p, int q, int v) {
    int res = 0;
    for (int i = MAXB; i >= 0; --i) {
        int d = (v >> i) & 1, nd = d ^ 1;
        if (cnt[ch[q][nd]] > cnt[ch[p][nd]]) {
            res |= (1 << i);
            p = ch[p][d]; q = ch[q][d];
        } else {
            p = ch[p][nd]; q = ch[q][nd];
        }
    }
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    root[0] = 0;
    vector<int> s(n + 1, 0);
    for (int i = 1; i <= n; ++i) { cin >> s[i]; s[i] ^= s[i-1]; insert(root[i], root[i-1], s[i]); }
    int tail = n;
    while (m--) {
        char op; cin >> op;
        if (op == 'A') {
            int x; cin >> x; tail++;
            s[tail] = s[tail-1] ^ x;
            insert(root[tail], root[tail-1], s[tail]);
        } else {
            int l, r, x; cin >> l >> r >> x;
            cout << query(root[l-1], root[r], x) << '\n';
        }
    }
    return 0;
}
