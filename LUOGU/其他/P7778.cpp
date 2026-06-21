#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, v;
    cin >> n >> v;
    vector<pair<long long,long long>> pts(n + 1);
    for (int i = 0; i <= n; i++) {
        cin >> pts[i].first >> pts[i].second;
    }
    sort(pts.begin(), pts.end());
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        long long dx = pts[i].first - pts[i-1].first;
        long long dy = pts[i].second - pts[i-1].second;
        long long dist2 = dx * dx + dy * dy;
        ans = (ans + dist2 % 998244353) % 998244353;
    }
    cout << ans << "\n";
    return 0;
}
