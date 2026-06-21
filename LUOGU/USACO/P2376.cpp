#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long,long long>> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    sort(a.begin(), a.end());
    long long sum = 0, ans = -1e18;
    for (int i = 0; i < n; i++) {
        ans = max(ans, sum - a[i].second);
        sum += a[i].first;
    }
    cout << ans << "\n";
    return 0;
}
