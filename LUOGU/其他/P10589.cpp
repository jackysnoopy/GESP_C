#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 200001;
int tr[MAXN], n;
void add(int i, int v) { for (; i <= n; i += i & (-i)) tr[i] += v; }
int sum(int i) { int s = 0; for (; i > 0; i -= i & (-i)) s += tr[i]; return s; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vector<int> Lbig(n+1,0), Lsmall(n+1,0), Rbig(n+1,0), Rsmall(n+1,0);
    for (int i = 1; i <= n; ++i) {
        Lbig[i] = sum(n) - sum(a[i]);
        Lsmall[i] = sum(a[i] - 1);
        add(a[i], 1);
    }
    for (int i = 1; i <= n; ++i) tr[i] = 0;
    for (int i = n; i >= 1; --i) {
        Rbig[i] = sum(n) - sum(a[i]);
        Rsmall[i] = sum(a[i] - 1);
        add(a[i], 1);
    }
    long long v = 0, h = 0;
    for (int i = 1; i <= n; ++i) { v += (long long)Lbig[i] * Rbig[i]; h += (long long)Lsmall[i] * Rsmall[i]; }
    cout << v << " " << h << '\n';
    return 0;
}
