#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, k, p, q;
        cin >> n >> k >> p >> q;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += a[i] % min(p, q);
        }

        cout << ans << "\n";
    }

    return 0;
}
