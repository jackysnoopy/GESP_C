#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, R;
    cin >> n >> R;
    vector<double> l(n), r(n);
    for (int i = 0; i < n; i++) {
        double x, y; cin >> x >> y;
        double d = sqrt((double)R * R - y * y);
        l[i] = x - d;
        r[i] = x + d;
    }
    // Greedy interval covering: sort by right endpoint
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) { return r[a] < r[b]; });
    int ans = 0;
    double last = -1e18;
    for (int i : idx) {
        if (l[i] > last) {
            ans++;
            last = r[i];
        }
    }
    cout << ans << "\n";
    return 0;
}
