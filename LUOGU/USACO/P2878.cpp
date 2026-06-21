#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> t(n), d(n);
    for (int i = 0; i < n; i++) cin >> t[i] >> d[i];
    // Sort by d[i]/t[i] descending (ratio of damage to time)
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return d[a] * t[b] > d[b] * t[a];
    });
    long long cur = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        int id = idx[i];
        ans += cur * d[id];
        cur += 2 * t[id];
    }
    cout << ans << "\n";
    return 0;
}
