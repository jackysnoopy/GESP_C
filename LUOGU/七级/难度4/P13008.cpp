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
        long long x, y;
        int k;
        cin >> x >> y >> k;

        vector<long long> a(k + 1);
        for (int i = 0; i <= k; i++) cin >> a[i];

        long long diff = abs(x - y);
        long long ans = 0;

        for (int i = k; i >= 0; i--) {
            long long power = 1LL << i;
            long long cnt = diff / power;
            ans += cnt * a[i];
            diff -= cnt * power;
        }

        cout << ans << "\n";
    }

    return 0;
}
