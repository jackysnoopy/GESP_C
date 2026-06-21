#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int>> seg(n);
    for (int i = 0; i < n; i++) cin >> seg[i].first >> seg[i].second;
    sort(seg.begin(), seg.end(), [](const pair<int,int>& a, const pair<int,int>& b) {
        return a.second < b.second;
    });
    int ans = 0, last = -1;
    for (int i = 0; i < n; i++) {
        if (seg[i].first >= last) { ans++; last = seg[i].second; }
    }
    cout << ans << "\n";
    return 0;
}
