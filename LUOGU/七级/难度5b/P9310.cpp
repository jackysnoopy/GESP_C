#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Fenwick {
    vector<int> tree;
    int n;
    Fenwick(int n) : tree(n + 1, 0), n(n) {}
    void update(int i, int delta) {
        for (; i <= n; i += i & (-i)) tree[i] += delta;
    }
    int query(int i) {
        int sum = 0;
        for (; i > 0; i -= i & (-i)) sum += tree[i];
        return sum;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> a(2 * n);
    for (int i = 0; i < 2 * n; i++) cin >> a[i];

    vector<int> L(n + 1, -1), R(n + 1, -1);
    for (int i = 0; i < 2 * n; i++) {
        if (L[a[i]] == -1) L[a[i]] = i + 1;
        else R[a[i]] = i + 1;
    }

    vector<pair<int, int>> inv(n);
    for (int i = 1; i <= n; i++) {
        inv[i - 1] = {L[i], R[i]};
    }

    sort(inv.begin(), inv.end());

    Fenwick fenw(2 * n);
    long long crossings = 0;

    for (auto& p : inv) {
        int l = p.first, r = p.second;
        crossings += fenw.query(l + 1, r - 1);
        fenw.update(r, 1);
    }

    cout << crossings + n << "\n";
    return 0;
}
