#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, b;
        cin >> n >> b;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        sort(a.begin(), a.end());
        int ans = 0;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            if (sum <= b) ans = i + 1;
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
