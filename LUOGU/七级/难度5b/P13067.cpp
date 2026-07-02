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
        int k, n;
        cin >> k >> n;
        
        vector<int> x(n), temp(n);
        for (int i = 0; i < n; i++) cin >> x[i];
        for (int i = 0; i < n; i++) cin >> temp[i];
        
        // We want to find the minimum number of thermometers
        // that could have produced the observed data
        
        // The data says: for each segment [x[i], x[i+1]), the temperature is temp[i]
        // For the last segment [x[n-1], k), the temperature is temp[n-1]
        // And for [0, x[0]), the temperature is temp[n-1]
        
        // A thermometer at position p with temperature T
        // affects all points that are closer to p than to any other thermometer
        // (with tie-breaking: use the clockwise thermometer)
        
        // We want to find the minimum number of thermometers
        
        // Key insight: for each temperature change, we need at least one thermometer
        // But consecutive segments with the same temperature might share a thermometer
        
        // Let's think about this differently:
        // For each segment, we know the temperature
        // We need to place thermometers such that each segment gets the right temperature
        
        // The minimum number of thermometers is at least the number of distinct temperatures
        // But it might be more because of the geometry
        
        // Let's use a greedy approach:
        // For each temperature change, we need a new thermometer
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int next = (i + 1) % n;
            if (temp[i] != temp[next]) {
                ans++;
            }
        }
        
        cout << "Case #" << t << ": " << max(ans, 1) << endl;
    }
    
    return 0;
}
