#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, x, y;
    cin >> n >> x >> y;
    vector<int> m(n), b(n);
    for (int i = 0; i < n; i++) cin >> m[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    sort(m.begin(), m.end());
    sort(b.begin(), b.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (b[i] > m[i]) ans += (long long)(b[i] - m[i]) * x;
        else ans += (long long)(m[i] - b[i]) * y;
    }
    cout << ans << "\n";
    return 0;
}
