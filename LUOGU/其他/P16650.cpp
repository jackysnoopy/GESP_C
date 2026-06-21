#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // "cannot be consumed on the day it expires, or on any day after"
        // Day 0 = today. Yogurt expires in A_i days means expires on day A_i.
        // Can consume on days 0, 1, ..., A_i - 1.
        // A_i = 1: can only consume on day 0. K cups per day.
        // A_i = 2: can consume on days 0, 1.
        //
        // Sort by expiry. Greedy: consume earliest-expiring first.
        sort(a.begin(), a.end());
        int ans = 0;
        int day = 0; // current day (0-indexed)
        int used = 0; // cups consumed today
        for (int i = 0; i < n; i++) {
            // This yogurt expires on day a[i], consume on day <= a[i]-1
            // We're on day 'day'. If day <= a[i]-1, consume it.
            if (day < a[i]) {
                ans++;
                used++;
                if (used == k) { day++; used = 0; }
            }
        }
        cout << "Case #" << t << ": " << ans << "\n";
    }
    return 0;
}
