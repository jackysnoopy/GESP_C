#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Binary search: can we make all cows have >= x happiness with c operations?
    // Each operation: pick a cow, increase its happiness by 1, cost 1
    auto check = [&](long long x) -> bool {
        long long need = 0;
        for (int i = 0; i < n; i++)
            if (a[i] < x) need += x - a[i];
        return need <= c;
    };
    long long lo = 0, hi = 1e12, ans = 0;
    while (lo <= hi) {
        long long mid = (lo+hi)/2;
        if (check(mid)) { ans = mid; lo = mid+1; }
        else hi = mid-1;
    }
    cout << ans << "\n";
    return 0;
}
