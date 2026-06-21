#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long ans = 1e18;
    for (int lo = 0; lo <= 100; lo++) {
        int hi = lo + 17;
        long long cost = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] < lo) cost += (long long)(lo - a[i]) * (lo - a[i]);
            else if (a[i] > hi) cost += (long long)(a[i] - hi) * (a[i] - hi);
        }
        ans = min(ans, cost);
    }
    cout << ans << "\n";
    return 0;
}
