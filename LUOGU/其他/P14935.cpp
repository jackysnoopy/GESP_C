#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int r, q, n, m;
        cin >> r >> q >> n >> m;
        int limit = m / 3;
        int strongBefore = min(r - 1, q * n);
        int weakBefore = max(0, r - 1 - q * n);
        int fullTeams = strongBefore / n;
        int rem = strongBefore % n;
        int cap = min(n, limit);
        int admittedFromStrong = fullTeams * cap + min(rem, cap);
        int admitted_before = admittedFromStrong + weakBefore;
        if (admitted_before <= m - 1) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
