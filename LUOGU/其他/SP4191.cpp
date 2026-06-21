#include <iostream>
#include <vector>
using namespace std;
long long C4(long long x) { return x * (x-1) * (x-2) * (x-3) / 24; }
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int mx = 0;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) { cin >> a[i]; mx = max(mx, a[i]); }
        vector<int> cnt(mx + 1, 0);
        for (int x : a) cnt[x]++;
        for (int i = 1; i <= mx; ++i)
            for (int j = 2 * i; j <= mx; j += i) cnt[i] += cnt[j];
        vector<int> mu(mx + 1, 1);
        vector<bool> comp(mx + 1, false);
        for (int i = 2; i <= mx; ++i) {
            if (!comp[i]) {
                mu[i] = -1;
                for (int j = 2 * i; j <= mx; j += i) {
                    comp[j] = true;
                    if (j / i % i == 0) mu[j] = 0;
                    else mu[j] = -mu[j];
                }
            }
        }
        long long ans = 0;
        for (int d = 1; d <= mx; ++d)
            ans += (long long)mu[d] * C4(cnt[d]);
        cout << ans << '\n';
    }
    return 0;
}
