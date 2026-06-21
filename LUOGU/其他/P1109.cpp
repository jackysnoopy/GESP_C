#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int a[101];
    for (int i = 0; i < n; i++) cin >> a[i];
    int L, R;
    cin >> L >> R;
    long long total = 0;
    for (int i = 0; i < n; i++) total += a[i];
    if (total < (long long)L * n || total > (long long)R * n) { cout << -1 << "\n"; return 0; }
    int best = 1000000000;
    for (int t = L; t <= R; t++) {
        int excess = 0, deficit = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > t) excess += a[i] - t;
            else deficit += t - a[i];
        }
        if (excess == deficit) best = min(best, excess);
    }
    if (best == 1000000000) cout << -1 << "\n";
    else cout << best << "\n";
    return 0;
}
