#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int n;
        cin >> n;
        vector<pair<long long, long long>> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i].second >> a[i].first;
        vector<long long> speeds(n);
        for (int i = 0; i < n; ++i) {
            long long v = a[i].second, w = a[i].first;
            long long mn = v, mx = v;
            for (int j = 0; j < n; ++j) {
                if (i == j) continue;
                if (a[j].first <= w) mn = max(mn, a[j].second);
                else mn = max(mn, v - (a[j].first - w));
            }
            speeds[i] = mn;
        }
        cout << *max_element(speeds.begin(), speeds.end()) << '\n';
    }
    return 0;
}
