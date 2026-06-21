#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<long long, long long>> cows;
    for (int i = 0; i < n; i++) {
        long long x, y;
        cin >> x >> y;
        cows.push_back({y, x});
    }
    sort(cows.begin(), cows.end());
    int l = 0, r = (int)cows.size() - 1;
    long long ans = 0;
    while (l <= r) {
        long long pairs = min(cows[l].second, cows[r].second);
        if (l == r) pairs = cows[l].second / 2;
        ans = max(ans, cows[l].first + cows[r].first);
        cows[l].second -= pairs;
        cows[r].second -= pairs;
        if (cows[l].second == 0) l++;
        if (cows[r].second == 0) r--;
    }
    cout << ans << "\n";
    return 0;
}
