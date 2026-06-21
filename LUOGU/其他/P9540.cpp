#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, y, z;
    if (!(cin >> n >> y >> z)) return 0;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    int cur = 0;
    int ai = 0, bi = 0;
    int ans = 0;
    while (ai < n || bi < n) {
        if (bi == n || (ai < n && a[ai] < b[bi])) {
            if (a[ai] == y) cur ^= 1;
            ++ai;
        } else {
            if (b[bi] == y) cur ^= 1;
            ++bi;
        }
        ++ans;
    }
    cout << ans << '\n';
    return 0;
}
