#include <iostream>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (int cs = 1; cs <= t; cs++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        int ans = 0;
        for (int bit = 19; bit >= 0; bit--) {
            int cnt = 0, mask = ans | (1<<bit);
            for (int i = 0; i < n; i++)
                if ((a[i] & mask) == mask) cnt++;
            if (cnt >= 2) ans = mask;
        }
        cout << "Case #" << cs << ": " << ans << "\n";
    }
    return 0;
}
