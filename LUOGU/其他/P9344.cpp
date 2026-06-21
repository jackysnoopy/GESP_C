#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        vector<int> c(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> c[i];
        long long ans = 0;
        for (int kind = 0; kind < 2; ++kind) {
            long long mn = (long long)1e18;
            bool seen = false;
            for (int i = 0; i < n; ++i) {
                if (c[i] == kind) {
                    if (!seen) { mn = a[i]; seen = true; continue; }
                    ans += a[i] + mn;
                    mn = (long long)1e18;
                    seen = false;
                }
            }
            if (seen) ans += 2 * mn;
        }
        cout << ans << '\n';
    }
    return 0;
}
