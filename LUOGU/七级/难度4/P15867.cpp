#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, t;
    cin >> c >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<long long> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans |= a[i];
        }

        cout << ans << "\n";
    }

    return 0;
}
