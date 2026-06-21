#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<long long> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    // Binary search on minimum total cost
    auto check = [&](long long mid) -> bool {
        long long need = 0;
        for (int i = 1; i <= n; i++) {
            if (a[i] > mid) need += (a[i] - mid + k - 1) / k;
        }
        return need <= n;
    };
    long long lo = 0, hi = 1e18, ans = hi;
    while (lo <= hi) {
        long long mid = (lo+hi)/2;
        if (check(mid)) { ans = mid; hi = mid-1; }
        else lo = mid+1;
    }
    cout << ans << "\n";
    return 0;
}
