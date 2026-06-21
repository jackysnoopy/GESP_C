#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    if (n <= 2) { cout << 0 << "\n"; return 0; }
    // Pattern: odd positions same value x, even positions same value y (x!=y)
    // Count freq of each value at odd and even positions
    map<int,int> odd, even;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) odd[a[i]]++;
        else even[a[i]]++;
    }
    int nodd = (n + 1) / 2, neven = n / 2;
    // Try all pairs of (val at odd, val at even)
    vector<pair<int,int>> topOdd, topEven;
    for (auto &p : odd) topOdd.push_back({p.second, p.first});
    for (auto &p : even) topEven.push_back({p.second, p.first});
    sort(topOdd.rbegin(), topOdd.rend());
    sort(topEven.rbegin(), topEven.rend());
    // Add dummy if empty
    if (topOdd.empty()) topOdd.push_back({0, 0});
    if (topEven.empty()) topEven.push_back({0, 0});
    int ans = n;
    // Try top candidates
    for (int i = 0; i < min(3, (int)topOdd.size()); i++) {
        for (int j = 0; j < min(3, (int)topEven.size()); j++) {
            int ov = topOdd[i].second, ev = topEven[j].second;
            if (ov == ev) continue;
            int cost = (nodd - topOdd[i].first) + (neven - topEven[j].first);
            ans = min(ans, cost);
        }
    }
    cout << ans << "\n";
    return 0;
}
