#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    cin >> n >> d;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long lo = 0, hi = 1e18, ans = 0;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        vector<long long> b(a);
        long long need = 0;
        bool ok = true;
        for (int i = n-1; i >= 0; i--) {
            if (b[i] >= mid) {
                need += (b[i] - mid) / d;
            } else {
                need -= (mid - b[i] + d - 1) / d;
            }
        }
        if (need >= 0) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
