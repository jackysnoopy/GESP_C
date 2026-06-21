#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n; cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end(), greater<long long>());
    long long basis[64] = {}, ans = 0;
    for (int i = 0; i < n; ++i) {
        long long x = a[i];
        for (int j = 62; j >= 0; --j) {
            if (!((x >> j) & 1)) continue;
            if (!basis[j]) { basis[j] = x; break; }
            x ^= basis[j];
        }
        if (x == 0) ans += a[i];
    }
    cout << ans << '\n';
    return 0;
}
