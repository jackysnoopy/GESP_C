#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<char,int>> events(n);
    for (int i = 0; i < n; i++) {
        cin >> events[i].first >> events[i].second;
    }
    // Binary search on answer
    // Check if min distance >= mid is achievable
    int lo = 1, hi = 1e9;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        // Try to place checkpoints with distance >= mid
        // Events are time-based: at time t, distance traveled is sum of 1/i
        // Actually this is more complex - need to simulate
        lo = mid; // simplified
        break;
    }
    // Direct approach: track cumulative distance
    double dist = 0;
    int cnt = 0;
    double target = 0;
    for (int i = 0; i < n; i++) {
        if (events[i].first == 'T') {
            target += events[i].second;
        } else {
            target += events[i].second * 1.0 / (cnt + 1);
        }
        // Count how many time events
    }
    // Proper solution: binary search + simulation
    int ans = 0;
    lo = 0; hi = 1e9;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        double totalDist = 0;
        int errors = 0;
        int lastErrorDist = 0;
        bool ok = true;
        double speed = 1.0;
        double curDist = 0;
        for (int i = 0; i < n; i++) {
            if (events[i].first == 'T') {
                curDist += events[i].second * speed;
            } else {
                curDist += events[i].second * speed;
                errors++;
                speed = 1.0 / (errors + 1);
            }
            if (curDist >= mid) { ok = false; break; }
        }
        if (ok) lo = mid + 1;
        else hi = mid - 1;
    }
    cout << lo << "\n";
    return 0;
}
