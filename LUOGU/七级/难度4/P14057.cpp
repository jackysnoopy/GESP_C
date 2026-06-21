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
        int n, m;
        cin >> n >> m;

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        sort(a.begin(), a.end());

        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (i == 0) ans += a[i];
            else ans += min(m, a[i]);
        }

        cout << ans << "\n";
    }

    return 0;
}
