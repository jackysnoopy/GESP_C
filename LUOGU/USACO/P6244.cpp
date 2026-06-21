#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> events(n);
    for (int i = 0; i < n; i++) {
        int t, l;
        cin >> t >> l;
        events[i] = {t + l, t};
    }
    sort(events.begin(), events.end());
    int ans = 0, lastEnd = 0;
    for (int i = 0; i < n; i++) {
        if (events[i].second >= lastEnd) {
            ans++;
            lastEnd = events[i].first;
        }
    }
    cout << ans << "\n";
    return 0;
}
