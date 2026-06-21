#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, d;
    cin >> n >> d;
    vector<int> h(n);
    for (int i = 0; i < n; i++) cin >> h[i];
    // Binary search on minimum happiness
    int lo = 0, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        long long cur = 0;
        int day = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (cur < mid) { day++; cur += h[i]; }
            else { cur = cur / 2 + h[i]; }
            if (cur >= mid && day <= d) continue;
        }
        // Simulate properly
        cur = 0;
        day = 1;
        int lastDay = 1;
        for (int i = 0; i < n; i++) {
            if (cur < mid) {
                lastDay = day;
                day++;
                cur += h[i];
                if (day > d + 1) { ok = false; break; }
            } else {
                cur = cur / 2 + h[i];
                lastDay = day;
            }
        }
        if (day - 1 <= d) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    // Output assignment
    long long cur = 0;
    int day = 1;
    for (int i = 0; i < n; i++) {
        if (cur < lo) { cout << day << "\n"; cur += h[i]; day++; }
        else { cout << day << "\n"; cur = cur / 2 + h[i]; }
    }
    return 0;
}
