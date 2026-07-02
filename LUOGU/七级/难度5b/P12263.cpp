#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    while (m--) {
        int l, r, v;
        cin >> l >> r >> v;
        for (int i = l; i <= r; i++) a[i] += v;
        vector<long long> b(n + 1);
        for (int i = 1; i <= n; i++) {
            long long best = a[i];
            long long cur = a[i];
            int pos = i;
            while (pos > 1) {
                cur = max(cur - 1, 0LL);
                pos--;
                best = max(best, a[pos]);
                if (a[pos] >= cur) {
                    best = a[pos];
                    break;
                }
            }
            b[i] = best;
        }
        set<long long> vals;
        for (int i = 1; i <= n; i++) vals.insert(b[i]);
        cout << vals.size() << "\n";
    }
    return 0;
}
