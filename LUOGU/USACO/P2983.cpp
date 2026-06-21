#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long B;
    cin >> n >> B;
    vector<pair<long long,long long>> choc(n);
    for (int i = 0; i < n; i++) cin >> choc[i].first >> choc[i].second;
    // Sort by price
    sort(choc.begin(), choc.end());
    long long ans = 0, rem = B;
    for (int i = 0; i < n; i++) {
        long long take = min(choc[i].second, rem / choc[i].first);
        ans += take;
        rem -= take * choc[i].first;
    }
    cout << ans << "\n";
    return 0;
}
