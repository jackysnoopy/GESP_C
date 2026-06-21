#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        int mx = a.back();
        vector<bool> can(mx+1, false);
        can[0] = true;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (can[a[i]]) continue;
            ans++;
            for (int j = a[i]; j <= mx; j++)
                if (can[j-a[i]]) can[j] = true;
        }
        cout << ans << "\n";
    }
    return 0;
}
