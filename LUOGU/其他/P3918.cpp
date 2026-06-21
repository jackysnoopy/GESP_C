#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> c(k);
    for (int i = 0; i < k; i++) cin >> c[i];
    sort(c.begin(), c.end(), greater<int>());
    if (k == 1) {
        cout << 0 << "\n";
        return 0;
    }
    long long ans = 0;
    int use0 = 0, use1 = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            ans += (long long)use0 * c[0];
            use0++;
        } else {
            ans += (long long)use1 * c[1];
            use1++;
        }
    }
    cout << ans << "\n";
    return 0;
}
