#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, d, l;
    cin >> n >> m >> d >> l;
    vector<int> s(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s.begin(), s.end(), greater<int>());
    // Binary search: can k cows drive?
    int lo = 0, hi = n, ans = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // Take the top mid cows, assign them to m lanes
        // Cow in position j (0-indexed) in lane has k_j cows ahead
        // Speed = max(S - D * k_j, 0) >= L
        // Need S >= L + D * k_j => k_j <= (S - L) / D
        bool ok = true;
        vector<int> cnt(m, 0);
        for (int i = 0; i < mid; i++) {
            // Assign to lane with minimum count
            int lane = 0;
            for (int j = 1; j < m; j++) {
                if (cnt[j] < cnt[lane]) lane = j;
            }
            if ((long long)s[i] - (long long)d * cnt[lane] < l) { ok = false; break; }
            cnt[lane]++;
        }
        if (ok) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
