#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, k;
    if (!(cin >> m >> k)) return 0;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) cin >> a[i];
    vector<long long> ans(m, -1);
    long long suffix = 0;
    for (int i = m - 1; i >= 0; --i) {
        suffix += a[i];
        ans[i] = suffix;
    }
    for (int i = 0; i < m; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << ' ' << '\n';
    return 0;
}
