#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        int n, m, C;
        cin >> n >> m >> C;
        
        vector<int> c1(m), c2(m);
        for (int i = 0; i < m; i++) cin >> c1[i];
        for (int i = 0; i < m; i++) cin >> c2[i];
        
        // Binary search on the answer
        double lo = 0, hi = 1e9;
        
        for (int iter = 0; iter < 100; iter++) {
            double mid = (lo + hi) / 2;
            
            // Check if we can achieve maximum load <= mid
            // For each time step, we need to assign lanes to directions
            // such that the load is <= mid
            
            // The load at time i for direction j is c[i][j] / (1 + number of dynamic lanes for j)
            // So we need: c[i][j] / (1 + lanes[i][j]) <= mid
            // => lanes[i][j] >= c[i][j] / mid - 1
            
            // For each time step, we need to assign lanes to directions
            // such that the total lanes used <= n
            // and the load constraint is satisfied
            
            // This is a feasibility problem
            // Let's check if it's possible
            
            bool feasible = true;
            
            // For each time step, compute the minimum lanes needed for each direction
            for (int i = 0; i < m; i++) {
                int need1 = max(0, (int)ceil(c1[i] / mid - 1));
                int need2 = max(0, (int)ceil(c2[i] / mid - 1));
                
                if (need1 + need2 > n) {
                    feasible = false;
                    break;
                }
            }
            
            if (feasible) hi = mid;
            else lo = mid;
        }
        
        cout << fixed << setprecision(10) << hi << endl;
    }
    
    return 0;
}
