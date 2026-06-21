#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, c;
    cin >> n >> c;
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    sort(x.begin(), x.end());
    int lo = 1, hi = x[n-1] - x[0], ans = 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int cnt = 1, last = x[0];
        for (int i = 1; i < n; i++) {
            if (x[i] - last >= mid) { cnt++; last = x[i]; }
        }
        if (cnt >= c) { ans = mid; lo = mid + 1; }
        else hi = mid - 1;
    }
    cout << ans << "\n";
    return 0;
}
