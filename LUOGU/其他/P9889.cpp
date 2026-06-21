#include <iostream>
#include <algorithm>
using namespace std;
int n;
long long m;
long long a[100001];
bool check(long long mid) {
    long long steps = 0;
    for (int i = 0; i < n; i++) {
        long long need = (mid + a[i] - 1) / a[i];
        if (i == 0) {
            steps += need * 2 - 1;
        } else {
            long long prevNeed = (mid + a[i - 1] - 1) / a[i - 1];
            long long saved = min(prevNeed, need);
            steps += (need - saved) * 2;
        }
    }
    return steps <= m;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        for (int i = 0; i < n; i++) cin >> a[i];
        long long lo = 0, hi = m / n * *min_element(a, a + n) + *min_element(a, a + n);
        hi = max(hi, 1LL);
        while (lo < hi) {
            long long mid = (lo + hi + 1) / 2;
            if (check(mid)) lo = mid;
            else hi = mid - 1;
        }
        cout << lo << "\n";
    }
    return 0;
}
