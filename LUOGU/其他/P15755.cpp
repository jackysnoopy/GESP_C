#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // Sort descending: heaviest at bottom, lightest at top
    // Load = sum of (weight_above / weight_current) for each box
    // To minimize: put heaviest at bottom
    sort(a.rbegin(), a.rend());
    long long sum = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0) ans += sum / a[i];
        sum += a[i];
    }
    cout << ans << "\n";
    return 0;
}
