#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int c, n;
    cin >> c >> n;

    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    for (int k = 1; k < n; k++) {
        int ans = 0;
        for (int t = 0; ; t++) {
            bool safe = true;
            for (int i = 0; i < n; i++) {
                if (v[i] + (t + 1) * (k > 0 ? 1 : 0) <= t + 1) {
                    safe = false;
                    break;
                }
            }
            if (!safe) {
                ans = t;
                break;
            }
        }
        cout << ans;
        if (k < n - 1) cout << " ";
    }
    cout << "\n";

    return 0;
}
