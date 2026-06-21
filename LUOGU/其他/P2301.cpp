#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, n;
    cin >> m >> n;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    sort(a.begin(), a.end());
    // Choose n pairs from m sticks, each person picks 2
    // Minimize sum of (L1-L2)^2
    // Greedy: pair consecutive elements after sorting
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long diff = a[2 * i + 1] - a[2 * i];
        ans += diff * diff;
    }
    cout << ans << "\n";
    return 0;
}
