#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    vector<pair<int,int>> seg(N);
    vector<int> val;
    for (int i = 0; i < N; i++) {
        cin >> seg[i].first >> seg[i].second;
        val.push_back(seg[i].first);
        val.push_back(seg[i].second);
    }
    sort(val.begin(), val.end());
    val.erase(unique(val.begin(), val.end()), val.end());
    int sz = val.size();
    vector<int> d(sz + 2, 0);
    for (auto &s : seg) {
        int l = lower_bound(val.begin(), val.end(), s.first) - val.begin() + 1;
        int r = lower_bound(val.begin(), val.end(), s.second) - val.begin() + 1;
        d[l]++; d[r]--;
    }
    long long ans = 0;
    int cur = 0;
    for (int i = 1; i < sz; i++) {
        cur += d[i];
        if (cur > 0) ans += val[i] - val[i-1];
    }
    cout << ans << "\n";
    return 0;
}
