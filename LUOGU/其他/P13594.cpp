#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long s, L, R;
    cin >> n >> s >> L >> R;
    vector<pair<long long, long long>> events(n);
    for (int i = 0; i < n; i++) cin >> events[i].first >> events[i].second;
    sort(events.begin(), events.end());
    
    // Simulate temperature changes. At each event time, temp changes by x_i.
    // We can reset temp to any value in [L,R] at any time.
    // Minimize number of resets.
    
    // Track the feasible range [lo, hi] of temperatures without resetting.
    // Initially [s, s].
    // When temp changes by x at time t, new range is [lo+x, hi+x].
    // If this range doesn't intersect [L,R], we must reset.
    // After reset, we can choose any temp in [L,R], so range becomes [L,R].
    
    long long lo = s, hi = s;
    int resets = 0;
    
    for (int i = 0; i < n; i++) {
        long long x = events[i].second;
        lo += x;
        hi += x;
        
        // Check if [lo, hi] intersects [L, R]
        long long nlo = max(lo, L);
        long long nhi = min(hi, R);
        
        if (nlo > nhi) {
            // Must reset
            resets++;
            // After reset, temp can be anything in [L,R]
            // Then apply the change x... wait, the change already happened.
            // Actually: the temp changed by x_i, and we need it in [L,R].
            // We can reset BEFORE the change (cost 1) and set to appropriate value,
            // or AFTER the change (cost 1) and set to any value in [L,R].
            // The problem says we can adjust at any time.
            // So after the change, if temp is out of range, we reset.
            lo = L;
            hi = R;
        } else {
            lo = nlo;
            hi = nhi;
        }
    }
    
    cout << resets << endl;
    return 0;
}
