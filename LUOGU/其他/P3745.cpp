#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll A, B, C;
    cin >> A >> B >> C;
    int n, m;
    cin >> n >> m;
    vector<ll> t(n), b(m);
    for (int i = 0; i < n; i++) cin >> t[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    sort(t.begin(), t.end());
    sort(b.begin(), b.end());
    // Binary search on the final time T
    ll lo = 0, hi = 1e9, ans = 1e18;
    while (lo <= hi) {
        ll mid = (lo+hi)/2;
        // Compute cost for all courses finishing by time mid
        ll costB = 0, costC = 0;
        for (int i = 0; i < m; i++) {
            if (b[i] > mid) costB += (b[i] - mid) * B;
        }
        ll maxB = 0;
        for (int i = 0; i < m; i++) {
            if (b[i] > mid) maxB = max(maxB, b[i] - mid);
        }
        // For each student, if t[i] < mid, penalty = C*(mid-t[i])^... 
        // Actually: student waits from t[i] to max of all course finish times
        // If max course time = mid, student penalty = max(0, mid - t[i]) * C
        for (int i = 0; i < n; i++) {
            if (mid > t[i]) costC += (mid - t[i]) * C;
        }
        ans = min(ans, costB + costC);
        lo = mid + 1;
    }
    // Also try without any B operations
    lo = 0; hi = 1e9;
    while (lo <= hi) {
        ll mid = (lo+hi)/2;
        ll costB = 0;
        for (int i = 0; i < m; i++) {
            if (b[i] > mid) costB += (b[i] - mid) * B;
        }
        ll costC = 0;
        for (int i = 0; i < n; i++) {
            if (mid > t[i]) costC += (mid - t[i]) * C;
        }
        ans = min(ans, costB + costC);
        if (costB + costC <= ans) hi = mid - 1;
        else lo = mid + 1;
    }
    cout << ans << "\n";
    return 0;
}
