#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    int sz = 2 * n;
    vector<long long> b(sz), c(sz);
    for (int i = 0; i < sz; i++) cin >> b[i];
    for (int i = 0; i < sz; i++) cin >> c[i];
    vector<pair<long long, int>> diff(sz);
    for (int i = 0; i < sz; i++) diff[i] = {b[i] - c[i], i};
    sort(diff.begin(), diff.end(), greater<>());
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += b[diff[i].second];
    for (int i = n; i < sz; i++) ans += c[diff[i].second];
    cout << ans << "\n";
    return 0;
}
