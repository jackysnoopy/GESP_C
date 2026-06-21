#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m;
    cin >> m;
    vector<long long> t(m), p(m);
    for (int i = 0; i < m; i++) cin >> t[i];
    for (int i = 0; i < m; i++) cin >> p[i];
    // Taxi problem: assign m taxis to m people. Minimize total distance.
    // This is assignment problem. For min total |t[i]-p[j]|:
    // Sort both arrays. Pair in order.
    sort(t.begin(), t.end());
    sort(p.begin(), p.end());
    long long ans = 0;
    for (int i = 0; i < m; i++) ans += abs(t[i] - p[i]);
    cout << ans << endl;
    return 0;
}
