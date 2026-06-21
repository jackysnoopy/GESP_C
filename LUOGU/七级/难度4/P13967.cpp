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
        int n, x, y;
        cin >> n >> x >> y;

        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];

        int min_a = *min_element(a.begin(), a.end());
        int max_a = *max_element(a.begin(), a.end());
        int min_b = *min_element(b.begin(), b.end());
        int max_b = *max_element(b.begin(), b.end());

        if (max_a - min_a > x || max_b - min_b > y) {
            cout << "-1\n";
            continue;
        }

        int ops = 0;
        for (int i = 0; i < n; i++) {
            int need_a = max(0, a[i] - min_a);
            int need_b = max(0, b[i] - min_b);
            ops = max(ops, max(need_a, need_b));
        }

        cout << ops << "\n";
    }

    return 0;
}
