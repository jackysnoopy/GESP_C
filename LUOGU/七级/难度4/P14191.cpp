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
        int n;
        long long f;
        cin >> n >> f;

        vector<long long> l(n), r(n);
        for (int i = 0; i < n; i++) cin >> l[i] >> r[i];

        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;
        sort(order.begin(), order.end(), [&](int x, int y) {
            return l[x] < l[y];
        });

        long long ans = 0;
        long long cur = f;

        for (int i = 0; i < n; i++) {
            int idx = order[i];
            ans += max(0LL, l[idx] - cur);
            ans += r[idx] - l[idx];
            cur = r[idx];
        }

        cout << ans << "\n";
        for (int i = 0; i < n; i++) {
            if (i) cout << " ";
            cout << order[i] + 1;
        }
        cout << "\n";
    }

    return 0;
}
