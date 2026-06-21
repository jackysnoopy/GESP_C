#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    sort(a.begin(), a.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int pos = lower_bound(a.begin(), a.end(), x) - a.begin();
        int best = (int)1e9;
        if (pos < m) best = min(best, a[pos] - x);
        if (pos > 0) best = min(best, x - a[pos - 1]);
        ans += best;
    }
    cout << ans << "\n";
    return 0;
}
