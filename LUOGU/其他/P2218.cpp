#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
vector<pair<int,int>> pts;
bool check(long long L) {
    for (int mask = 0; mask < 8; mask++) {
        vector<long long> vals(n);
        for (int i = 0; i < n; i++) {
            vals[i] = pts[i].first;
            if (mask & 1) vals[i] = -vals[i] + L;
            if (mask & 2) vals[i] = pts[i].second;
            if (mask & 4) vals[i] = -pts[i].second + L;
        }
        long long mn = *min_element(vals.begin(), vals.end());
        long long mx = *max_element(vals.begin(), vals.end());
        if (mx - mn <= L) return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    pts.resize(n);
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    long long lo = 0, hi = 2e9;
    while (lo < hi) {
        long long mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << endl;
    return 0;
}