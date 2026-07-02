#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    string left, right;
    cin >> left >> right;
    
    // Y-shaped intersection with two lanes
    // Left lane cars: L or R (left or right turn)
    // Right lane cars: L or R
    
    // Left turn from left lane: uses x at time t
    // Right turn from left lane: uses x at t, junction at t+0.5, y at t+1
    // Left turn from right lane: uses y at t, junction at t+0.5, x at t+1
    // Right turn from right lane: uses y at t
    
    // Conflict: left lane R and right lane L both use junction at t+0.5
    // So they cannot both be scheduled at times t and t+0.5 where t differs by 0.5
    
    // Simplified: if left[i] = R and right[j] = L, they cannot be scheduled
    // at times where their junction usage overlaps
    
    // For now, greedy scheduling
    int time = 0;
    int li = 0, ri = 0;
    
    while (li < n || ri < m) {
        time++;
        
        bool leftCanGo = (li < n);
        bool rightCanGo = (ri < m);
        
        if (leftCanGo && rightCanGo) {
            // Check for conflicts
            if (left[li] == 'R' && right[ri] == 'L') {
                // Conflict - only one can go
                // Let left go first
                li++;
            } else {
                // No conflict, both can go
                li++;
                ri++;
            }
        } else if (leftCanGo) {
            li++;
        } else {
            ri++;
        }
    }
    
    // Add time for last car to exit
    time++;
    
    cout << time << "\n";
    return 0;
}
