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

        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            int target = n - i;
            if (a[i] < target) {
                ans += target - a[i];
                a[i] = target;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
