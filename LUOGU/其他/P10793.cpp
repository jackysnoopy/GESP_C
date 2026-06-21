#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, w;
        cin >> n >> w;
        vector<pair<int, int>> intervals(n);
        for (int i = 0; i < n; i++) cin >> intervals[i].first >> intervals[i].second;
        // Sort by left endpoint
        sort(intervals.begin(), intervals.end());
        int groups = 0;
        int i = 0;
        while (i < n) {
            groups++;
            // Start a new group
            int curL = intervals[i].first, curR = intervals[i].second;
            i++;
            while (i < n) {
                int newL = max(curL, intervals[i].first);
                int newR = min(curR, intervals[i].second);
                if (newR - newL + 1 >= w) {
                    curL = newL;
                    curR = newR;
                    i++;
                } else {
                    break;
                }
            }
        }
        cout << groups << "\n";
    }
    return 0;
}
