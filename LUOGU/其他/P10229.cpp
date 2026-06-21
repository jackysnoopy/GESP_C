#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n, t, a, b;
    cin >> n >> t >> a >> b;
    vector<long long> k(n);
    for (int i = 0; i < n; i++) cin >> k[i];
    long long ans = 0;
    for (int full = n; full >= 0; full--) {
        long long time_needed = full * a + (n - full) * b;
        if (time_needed > t) continue;
        long long rem = t - time_needed;
        int cnt = 0;
        for (int i = 0; i < full; i++) cnt++;
        for (int i = full; i < n; i++) {
            if (b <= rem) { cnt++; rem -= b; }
            else break;
        }
        ans = max(ans, (long long)cnt);
    }
    cout << ans << "\n";
    return 0;
}
