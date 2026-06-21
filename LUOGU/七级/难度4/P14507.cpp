#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];

    vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + b[i];

    while (q--) {
        long long m;
        cin >> m;

        if (m == 0) {
            cout << "-1\n";
            continue;
        }

        int ans = -1;
        for (int k = 1; k <= n; k++) {
            long long max_mex = 0;
            for (int i = 0; i < k; i++) {
                max_mex += a[i] + 1;
            }
            if (max_mex >= m) {
                ans = k;
                break;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
