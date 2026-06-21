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
        cin >> n;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        vector<int> order(n);
        for (int i = 0; i < n; i++) order[i] = i;
        sort(order.begin(), order.end(), [&](int x, int y) { return a[x] > a[y]; });

        vector<bool> used(n, false);
        int max_a = -1e9;
        int mex = 0;

        for (int k = 1; k <= n; k++) {
            int idx = order[k - 1];
            used[b[idx]] = true;
            max_a = max(max_a, a[idx]);

            while (mex < n && used[mex]) mex++;

            cout << max_a - mex << "\n";
        }
    }

    return 0;
}
