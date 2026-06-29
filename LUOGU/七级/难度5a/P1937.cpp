#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

struct Cow {
    int a, b, idx;
};

int n, m;
int cap[100005];
int tree[400005];

void build(int node, int l, int r) {
    if (l == r) {
        tree[node] = cap[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(node * 2, l, mid, pos, val);
    else update(node * 2 + 1, mid + 1, r, pos, val);
    tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 1e9;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l + r) / 2;
    return min(query(node * 2, l, mid, ql, qr), query(node * 2 + 1, mid + 1, r, ql, qr));
}

int findFirst(int node, int l, int r, int ql, int qr) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    if (qr <= mid) return findFirst(node * 2, l, mid, ql, qr);
    if (ql > mid) return findFirst(node * 2 + 1, mid + 1, r, ql, qr);
    if (tree[node * 2] > 0) return findFirst(node * 2 + 1, mid + 1, r, ql, qr);
    return findFirst(node * 2, l, mid, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
    }
    
    vector<Cow> cows(m);
    for (int i = 0; i < m; i++) {
        cin >> cows[i].a >> cows[i].b;
        cows[i].idx = i;
    }
    
    sort(cows.begin(), cows.end(), [](const Cow& x, const Cow& y) {
        return x.b < y.b || (x.b == y.b && x.a < y.a);
    });
    
    build(1, 1, n);
    
    int ans = 0;
    for (int i = 0; i < m; i++) {
        int a = cows[i].a, b = cows[i].b;
        if (query(1, 1, n, a, b) > 0) {
            int pos = findFirst(1, 1, n, a, b);
            update(1, 1, n, pos, cap[pos] - 1);
            cap[pos]--;
            ans++;
        }
    }
    
    cout << ans << "\n";
    return 0;
}