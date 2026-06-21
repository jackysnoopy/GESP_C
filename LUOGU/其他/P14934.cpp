#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; long long m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    long long mx = *max_element(a.begin(), a.end());
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long diff = mx - a[i];
        ans = max(ans, (diff + m) / (m + 1));
    }
    cout << ans << "\n";
    return 0;
}
