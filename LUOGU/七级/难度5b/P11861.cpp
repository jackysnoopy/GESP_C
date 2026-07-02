#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000002;
const long long INF = 1e18;

long long tree[MAXN * 4];
long long lazy[MAXN * 4];

void push(int node) {
    if (lazy[node] != 0) {
        tree[node * 2] += lazy[node];
        lazy[node * 2] += lazy[node];
        tree[node * 2 + 1] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
        lazy[node] = 0;
    }
}

void pull(int node) {
    tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

void update(int node, int l, int r, int ql, int qr, long long val) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    push(node);
    int mid = (l + r) / 2;
    update(node * 2, l, mid, ql, qr, val);
    update(node * 2 + 1, mid + 1, r, ql, qr, val);
    pull(node);
}

void setPoint(int node, int l, int r, int pos, long long val) {
    if (l == r) {
        tree[node] = val;
        lazy[node] = 0;
        return;
    }
    push(node);
    int mid = (l + r) / 2;
    if (pos <= mid)
        setPoint(node * 2, l, mid, pos, val);
    else
        setPoint(node * 2 + 1, mid + 1, r, pos, val);
    pull(node);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    const int MOD = 1000003;
    long long last = 0;

    vector<long long> taskVal(MAXN, 0);

    for (int i = 0; i < q; i++) {
        char c;
        cin >> c;
        if (c == 'A') {
            long long sp, tp;
            cin >> sp >> tp;
            long long s = (sp + last) % MOD;
            long long t = (tp + last) % MOD;
            if (s == 0) s = MOD;
            if (t == 0) t = MOD;

            if (s > 1)
                update(1, 1, MAXN - 1, 1, s - 1, t);
            setPoint(1, 1, MAXN - 1, s, s + t);
            taskVal[s] = s + t;
        } else {
            long long xp;
            cin >> xp;
            long long x = (xp + last) % MOD;
            if (x == 0) x = MOD;

            long long s = x;
            long long t = taskVal[x] - s;

            if (s > 1)
                update(1, 1, MAXN - 1, 1, s - 1, -t);
            setPoint(1, 1, MAXN - 1, s, 0);
            taskVal[s] = 0;
        }

        last = tree[1];
        cout << last << "\n";
    }

    return 0;
}
