#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p;
    cin >> n >> p;
    vector<int> a(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    vector<int> diff(n + 2, 0);
    while (p--) {
        int x, y, z;
        cin >> x >> y >> z;
        diff[x] += z;
        diff[y + 1] -= z;
    }
    int ans = INT_MAX, cur = 0;
    for (int i = 1; i <= n; i++) {
        cur += diff[i];
        ans = min(ans, a[i] + cur);
    }
    cout << ans << "\n";
    return 0;
}
