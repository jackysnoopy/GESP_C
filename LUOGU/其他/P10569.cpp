#include <iostream>
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
        long long a[100001];
        for (int i = 0; i < n; i++) cin >> a[i];
        // Greedy: always push from the end with larger value
        long long ans = 0;
        int l = 0, r = n - 1;
        while (l <= r) {
            if (a[l] >= a[r]) {
                ans += a[l];
                // Cascade to the right
                long long energy = a[l];
                while (l <= r && energy >= a[l]) {
                    energy = a[l];
                    l++;
                }
                // l is now at the first pillar that wasn't knocked down
                // Its height decreased by the remaining energy
                if (l <= r) a[l] -= energy;
            } else {
                ans += a[r];
                long long energy = a[r];
                while (l <= r && energy >= a[r]) {
                    energy = a[r];
                    r--;
                }
                if (l <= r) a[r] -= energy;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
