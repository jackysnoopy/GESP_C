#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 500001;
int tr[MAXN], n;
void add(int i, int v) { for (; i <= n; i += i & (-i)) tr[i] += v; }
int sum(int i) { int s = 0; for (; i > 0; i -= i & (-i)) s += tr[i]; return s; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int m; cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) { cin >> a[i]; add(i, a[i] - a[i-1]); }
    while (m--) {
        int op; cin >> op;
        if (op == 1) { int l, r, x; cin >> l >> r >> x; add(l, x); add(r + 1, -x); }
        else { int x; cin >> x; cout << sum(x) << '\n'; }
    }
    return 0;
}
