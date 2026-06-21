#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    long long h[1001], v[1001];
    for (int i = 0; i < n - 1; i++) cin >> h[i];
    for (int i = 0; i < m - 1; i++) cin >> v[i];
    sort(h, h + n - 1, greater<long long>());
    sort(v, v + m - 1, greater<long long>());
    long long ans = 0;
    int hi = 0, vi = 0;
    long long hc = 1, vc = 1;
    while (hi < n - 1 || vi < m - 1) {
        if (vi >= m - 1 || (hi < n - 1 && h[hi] >= v[vi])) {
            ans += h[hi] * vc;
            hc++; hi++;
        } else {
            ans += v[vi] * hc;
            vc++; vi++;
        }
    }
    cout << ans << "\n";
    return 0;
}
