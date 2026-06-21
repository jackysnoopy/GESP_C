#include <iostream>
#include <vector>
using namespace std;

struct BIT {
    int n; vector<int> t;
    BIT(int n) : n(n), t(n + 1, 0) {}
    void add(int i, int v) { for (; i <= n; i += i & -i) t[i] += v; }
    int sum(int i) { int r = 0; for (; i > 0; i -= i & -i) r += t[i]; return r; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    BIT st(n), ed(n);
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1) { st.add(l, 1); ed.add(r, 1); }
        else cout << st.sum(r) - ed.sum(l - 1) << "\n";
    }
    return 0;
}
