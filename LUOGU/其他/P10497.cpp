#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 8001;
int tr[MAXN], n;
void add(int i, int v) { for (; i <= n; i += i & (-i)) tr[i] += v; }
int sum(int i) { int s = 0; for (; i > 0; i -= i & (-i)) s += tr[i]; return s; }
int kth(int k) {
    int pos = 0;
    for (int pw = 1 << 12; pw > 0; pw >>= 1)
        if (pos + pw <= n && tr[pos + pw] < k) { pos += pw; k -= tr[pos]; }
    return pos + 1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    vector<int> v(n + 1), ans(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    for (int i = 1; i <= n; ++i) add(i, 1);
    for (int i = n; i >= 1; --i) {
        int k = v[i] + 1;
        int val = kth(k);
        ans[i] = val;
        add(val, -1);
    }
    for (int i = 1; i <= n; ++i) cout << ans[i] << '\n';
    return 0;
}
