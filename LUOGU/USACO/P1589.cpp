#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, L;
    cin >> n >> L;
    vector<pair<int,int>> seg(n);
    for (int i = 0; i < n; i++) cin >> seg[i].first >> seg[i].second;
    sort(seg.begin(), seg.end());
    long long ans = 0;
    long long cur = -1;
    for (int i = 0; i < n; i++) {
        if (seg[i].first > cur) {
            long long len = seg[i].second - seg[i].first;
            ans += (len + L) / L;
            cur = seg[i].first + ((len + L) / L) * L;
        } else if (seg[i].second > cur) {
            long long len = seg[i].second - cur;
            ans += (len + L - 1) / L;
            cur += ((len + L - 1) / L) * L;
        }
    }
    cout << ans << "\n";
    return 0;
}
