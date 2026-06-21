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
        long long n, p;
        cin >> n >> p;
        vector<long long> val(n);
        for (long long i = 0; i < n; ++i) val[i] = (i % p == 0 ? 1 : 0);
        long long inv2 = (p + 1) / 2;
        vector<long long> pref(n + 1, 0);
        for (int i = 0; i < n; ++i) pref[i + 1] = (pref[i] + val[i]) % p;
        long long total = pref[n];
        vector<long long> ans(n);
        for (int k = 0; k < n; ++k) {
            long long v = 0;
            if (k == 0) {
                v = total;
            } else if (k % 2 == 0) {
                v = total;
                for (int i = 0; i + k < n; ++i) v = (v + val[i] * val[i + k]) % p;
            } else {
                for (int i = 0; i + k < n; ++i) v = (v + val[i] * val[i + k]) % p;
                long long adj = 0;
                for (int i = 0; i + 1 < n; ++i) adj = (adj + val[i] * val[i + 1]) % p;
                v = (v + adj) % p;
                v = (v * inv2) % p;
            }
            ans[k] = v;
        }
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
