#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAX_BITS = 60;

struct TrieNode {
    int child[2];
    int cnt;
    TrieNode() {
        child[0] = child[1] = -1;
        cnt = 0;
    }
};

TrieNode trie[6000005];
int tot = 0;

int new_node() {
    trie[++tot] = TrieNode();
    return tot;
}

void insert(ll x) {
    int u = 1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if (trie[u].child[bit] == -1) {
            trie[u].child[bit] = new_node();
        }
        u = trie[u].child[bit];
        trie[u].cnt++;
    }
}

void erase(ll x) {
    int u = 1;
    for (int i = MAX_BITS - 1; i >= 0; i--) {
        int bit = (x >> i) & 1;
        u = trie[u].child[bit];
        trie[u].cnt--;
    }
}

ll max_xor(int u1, int u2, int bit) {
    if (bit < 0 || u1 == -1 || u2 == -1) return 0;
    ll res = 0;
    if (trie[u1].child[0] != -1 && trie[u2].child[1] != -1) {
        res = max(res, (1LL << bit) + max_xor(trie[u1].child[0], trie[u2].child[1], bit - 1));
    }
    if (trie[u1].child[1] != -1 && trie[u2].child[0] != -1) {
        res = max(res, (1LL << bit) + max_xor(trie[u1].child[1], trie[u2].child[0], bit - 1));
    }
    if (res == 0) {
        if (trie[u1].child[0] != -1 && trie[u2].child[0] != -1) {
            res = max(res, max_xor(trie[u1].child[0], trie[u2].child[0], bit - 1));
        }
        if (trie[u1].child[1] != -1 && trie[u2].child[1] != -1) {
            res = max(res, max_xor(trie[u1].child[1], trie[u2].child[1], bit - 1));
        }
    }
    return res;
}

int query(int u, ll x, int bit) {
    if (u == -1 || bit < 0) return trie[u].cnt;
    int b = (x >> bit) & 1;
    if (b == 0) {
        int lc = trie[u].child[0], rc = trie[u].child[1];
        if (lc == -1) return query(rc, x, bit - 1);
        if (rc == -1) return query(lc, x, bit - 1);
        return max(query(lc, x, bit - 1), query(rc, x, bit - 1));
    } else {
        int lc = trie[u].child[0], rc = trie[u].child[1];
        if (lc == -1 || rc == -1) {
            int c = (lc != -1) ? lc : rc;
            return query(c, x, bit - 1);
        }
        ll mx = max_xor(lc, rc, bit - 1);
        ll lim = x & ((1LL << bit) - 1);
        if (mx < lim) {
            return trie[lc].cnt + trie[rc].cnt;
        } else {
            return max(query(lc, x, bit - 1), query(rc, x, bit - 1));
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    ll x;
    cin >> n >> q >> x;

    new_node();

    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        insert(a);
    }

    cout << query(1, x, MAX_BITS - 1) << "\n";

    for (int i = 0; i < q; i++) {
        int pos;
        ll val;
        cin >> pos >> val;
        pos--;

        int u = 1;
        for (int j = MAX_BITS - 1; j >= 0; j--) {
            int bit = (val >> j) & 1;
            u = trie[u].child[bit];
        }
        ll old_val = 0;
        int uu = 1;
        for (int j = MAX_BITS - 1; j >= 0; j--) {
            int bit = (uu >> j) & 1;
            if (trie[uu].child[bit] != -1 && trie[trie[uu].child[bit]].cnt > 0) {
                old_val |= (1LL << j);
                uu = trie[uu].child[bit];
            } else {
                uu = trie[uu].child[1 - bit];
            }
        }

        erase(old_val);
        insert(val);
        cout << query(1, x, MAX_BITS - 1) << "\n";
    }

    return 0;
}
