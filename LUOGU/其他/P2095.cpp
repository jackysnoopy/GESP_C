#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(m);
    for (int i = 0; i < m; i++) cin >> a[i];
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int sum = 0;
        for (int j = 0; j < x; j++) { int v; cin >> v; sum += a[v - 1]; }
        if (sum >= k) ans++;
    }
    cout << ans << "\n";
    return 0;
}
