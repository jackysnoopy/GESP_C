#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int z; cin >> z;
    while (z--) {
        int n, m; cin >> n >> m;
        vector<int> t(m), j(m), ii(m);
        for (int i = 0; i < m; i++) cin >> t[i] >> j[i] >> ii[i];
        int lo = 1, hi = m, ans = m;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            vector<int> cnt(n + 1, 0);
            bool ok = true;
            for (int i = 0; i < mid; i++) cnt[j[i]]++;
            for (int i = 1; i <= n; i++) {
                if (cnt[i] > 0 && cnt[i] - 1 != ii[0]) ok = false;
            }
            if (ok) { ans = mid; hi = mid - 1; }
            else lo = mid + 1;
        }
        cout << ans << endl;
    }
    return 0;
}