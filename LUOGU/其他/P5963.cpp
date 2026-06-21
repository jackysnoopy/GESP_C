#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    vector<int> vals(2 * n);
    for (int i = 0; i < n; i++) {
        vals[2 * i] = a[i];
        vals[2 * i + 1] = b[i];
    }
    sort(vals.begin(), vals.end());
    long long ans = 0;
    for (int i = 0; i < 2 * n; i += 2) {
        ans -= vals[i];
    }
    for (int i = 1; i < 2 * n; i += 2) {
        ans += vals[i];
    }
    cout << ans << "\n";
    return 0;
}
