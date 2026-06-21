#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    // 贪心策略：买便宜的商品，花贵的钱
    sort(a.begin(), a.end());
    sort(b.rbegin(), b.rend());

    long long ans = 0;
    int k = min(n, m);
    for (int i = 0; i < k; i++) {
        ans += max(0, b[i] - a[i]);
    }

    cout << ans << "\n";

    return 0;
}
