#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, m;
        long long L, V;
        cin >> n >> m >> L >> V;
        vector<long long> d(n), v(n), a(n);
        for (int i = 0; i < n; i++) cin >> d[i] >> v[i] >> a[i];
        vector<long long> p(m);
        for (int i = 0; i < m; i++) cin >> p[i];
        sort(p.begin(), p.end());
        
        // For each car, determine which detectors can catch it speeding
        // A car speeds when v(t)^2 = v_i^2 + 2*a_i*(x - d_i) > V^2
        // i.e., at position x, speed^2 > V^2
        
        // Determine the speeding interval for each car
        // If a_i == 0: car moves at constant speed v_i
        //   If v_i > V: speeding everywhere [d_i, exit]
        //   If v_i <= V: never speeding
        // If a_i > 0: speed increases
        //   If v_i > V: speeding from d_i onwards
        //   If v_i == V: speeding immediately after d_i (since a>0, speed > V for x > d_i)
        //   Actually at x=d_i, speed = v_i. If v_i > V, speeding. If v_i <= V, need to find when speed > V
        //   v_i^2 + 2*a_i*(x-d_i) > V^2 => x > d_i + (V^2 - v_i^2)/(2*a_i)
        //   If v_i >= V: speeding from d_i (or d_i+epsilon for v_i=V)
        //   Wait: at exactly the detector position, is the speed measured?
        //   "若这辆车的瞬时速度超过了道路限速 V" - strictly greater
        //   So at position x: speed = sqrt(v_i^2 + 2*a_i*(x - d_i)) > V iff v_i^2 + 2*a_i*(x-d_i) > V^2
        
        // For a_i < 0: speed decreases
        //   If v_i > V: speeding until speed drops to V
        //   Speed > V when x < d_i + (V^2 - v_i^2)/(2*a_i)  (note: a_i < 0, so (V^2 - v_i^2)/(2*a_i) > 0)
        //   If v_i <= V: never speeding
        
        // Exit position: min(L, position where speed = 0)
        // Speed = 0 when v_i^2 + 2*a_i*(x - d_i) = 0 => x = d_i + v_i^2 / (2*(-a_i)) for a_i < 0
        
        int speedingCount = 0;
        vector<vector<int>> catchDetectors(n); // which detectors catch each car
        
        for (int i = 0; i < n; i++) {
            // Determine speeding interval [speedStart, speedEnd)
            double speedStart = d[i], speedEnd;
            
            if (a[i] == 0) {
                if (v[i] > V) {
                    speedEnd = L;
                } else {
                    catchDetectors[i].clear();
                    continue;
                }
            } else if (a[i] > 0) {
                if (v[i] > V) {
                    speedEnd = L;
                } else {
                    // Find position where speed > V
                    // v_i^2 + 2*a_i*(x-d_i) > V^2
                    // x > d_i + (V^2 - v_i^2) / (2*a_i)
                    double x0 = d[i] + (double)(V * V - v[i] * v[i]) / (2.0 * a[i]);
                    if (x0 < d[i]) x0 = d[i];
                    if (v[i] >= V) x0 = d[i];
                    speedStart = x0;
                    speedEnd = L;
                    if (speedStart >= L) {
                        catchDetectors[i].clear();
                        continue;
                    }
                }
            } else {
                // a[i] < 0
                if (v[i] <= V) {
                    catchDetectors[i].clear();
                    continue;
                }
                // Speed > V until position x0 where speed = V
                // v_i^2 + 2*a_i*(x-d_i) = V^2
                // x = d_i + (V^2 - v_i^2) / (2*a_i)
                // Since a_i < 0 and v_i > V: (V^2 - v_i^2) < 0, divided by 2*a_i < 0 = positive
                double x0 = d[i] + (double)(V * V - v[i] * v[i]) / (2.0 * a[i]);
                speedEnd = x0;
                // Also check if car stops (speed = 0)
                double xStop = d[i] + (double)(v[i] * v[i]) / (2.0 * (-a[i]));
                speedEnd = min(speedEnd, xStop);
                speedEnd = min(speedEnd, (double)L);
                if (speedEnd <= d[i]) {
                    catchDetectors[i].clear();
                    continue;
                }
            }
            
            // Find detectors in [speedStart, speedEnd)
            // Speed at detector position p[j] must be > V
            // p[j] must be in [d_i, exit_pos] and speed > V at p[j]
            
            // Find first detector >= ceil(speedStart) or >= speedStart
            // Actually detectors are at integer positions, and we need speed(p[j]) > V
            // For continuous: speed > V in (speedStart, speedEnd) typically
            // At exactly speedStart, speed = V (not > V)
            
            int lo = (int)(lower_bound(p.begin(), p.end(), (long long)(speedStart) + 1) - p.begin());
            // Actually we need to be more precise with the boundary
            // speedStart is the position where speed becomes > V
            // At speedStart exactly, speed = V (for v_i < V, a_i > 0 case)
            // For v_i > V cases, speedStart = d_i and speed > V at d_i itself
            
            // Let's compute speed at each detector position precisely
            for (int j = 0; j < m; j++) {
                if (p[j] < d[i] || p[j] > L) continue;
                // Check if car has exited before reaching this detector
                if (a[i] < 0) {
                    double xStop = d[i] + (double)(v[i] * v[i]) / (2.0 * (-a[i]));
                    if (p[j] > xStop + 1e-9) continue;
                }
                long long speedSq = v[i] * v[i] + 2LL * a[i] * (p[j] - d[i]);
                if (speedSq > V * V) {
                    catchDetectors[i].push_back(j);
                }
            }
            
            if (!catchDetectors[i].empty()) speedingCount++;
        }
        
        // For the second answer: maximize detectors to remove while still catching all speeding cars
        // This is equivalent to: find minimum detectors to keep
        // Which is: for each speeding car, we need at least one of its detectors to be kept
        // This is a hitting set / set cover problem
        // But we can be smarter: sort detectors, and use greedy interval covering
        
        // For each speeding car, it has a set of detectors. We want minimum detectors to keep.
        // Each speeding car has detectors that form a contiguous range (since detectors are sorted by position)
        // and the speeding interval is contiguous. So catchDetectors[i] is a contiguous range of indices.
        
        // Now we have intervals on detector indices. Find minimum number of points to hit all intervals.
        // This is the classic interval scheduling / greedy: sort by right endpoint, greedily pick.
        
        struct Interval { int l, r; };
        vector<Interval> intervals;
        for (int i = 0; i < n; i++) {
            if (!catchDetectors[i].empty()) {
                intervals.push_back({catchDetectors[i][0], catchDetectors[i].back()});
            }
        }
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });
        int keep = 0, lastKept = -1;
        for (auto& iv : intervals) {
            if (iv.l > lastKept) {
                keep++;
                lastKept = iv.r;
            }
        }
        
        cout << speedingCount << " " << (m - keep) << "\n";
    }
    return 0;
}
