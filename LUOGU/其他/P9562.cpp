#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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
        for (int i = 0; i < n; ++i) cin >> a[i];
        int ans = 0;
        for (int bit = 0; bit < 60; ++bit) {
            long long mask = 1LL << bit;
            long long xr = 0;
            for (int i = 0; i < n; ++i) xr ^= (a[i] & mask);
            if (xr != 0) ++ans;
        }
        cout << ans << '\n';
    }
    return 0;
}
