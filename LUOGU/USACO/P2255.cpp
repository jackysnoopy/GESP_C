#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>> seg(n);
    for (int i = 0; i < n; i++) cin >> seg[i].first >> seg[i].second;
    sort(seg.begin(), seg.end());
    // Greedy: assign each segment to one of two "tracks"
    // Each track maintains its last end time
    int end1 = -1, end2 = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int s = seg[i].first, e = seg[i].second;
        if (s >= end1) {
            end1 = e;
            ans++;
        } else if (s >= end2) {
            end2 = e;
            ans++;
        }
        // If both tracks occupied, skip this segment
    }
    cout << ans << "\n";
    return 0;
}
