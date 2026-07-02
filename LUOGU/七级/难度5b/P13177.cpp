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
        int c;
        cin >> c;
        
        // 2*c tours, 2 from each camp
        // Tour i starts at camp floor((i+1)/2)
        // Tour i ends at camp E[i], leaves at hour L[i], duration D[i]
        
        vector<int> E(2*c), L(2*c), D(2*c);
        for (int i = 0; i < 2*c; i++) {
            cin >> E[i] >> L[i] >> D[i];
        }
        
        // We need to find a route that:
        // 1. Starts at camp 1
        // 2. Visits each tour exactly once
        // 3. Ends at camp 1
        // 4. Minimizes total time
        
        // This is a Hamiltonian path problem, which is NP-hard
        // But for the given constraints, we can use dynamic programming
        
        // Let's use DP with bitmasks
        // dp[mask][camp] = minimum time to reach camp after visiting tours in mask
        
        int n = 2 * c;
        int full_mask = (1 << n) - 1;
        
        // dp[mask][camp] = minimum time
        vector<vector<long long>> dp(1 << n, vector<long long>(c + 1, 1e18));
        
        // Start at camp 1 at hour 0
        dp[0][1] = 0;
        
        for (int mask = 0; mask <= full_mask; mask++) {
            for (int camp = 1; camp <= c; camp++) {
                if (dp[mask][camp] >= 1e18) continue;
                
                // Try to take a tour from this camp
                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) continue; // Already taken
                    
                    int start_camp = (i / 2) + 1;
                    if (start_camp != camp) continue; // Tour doesn't start here
                    
                    // Calculate when we can take this tour
                    long long current_time = dp[mask][camp];
                    long long tour_start = L[i];
                    
                    // We might need to wait for the tour to start
                    // Tours run daily (every 24 hours)
                    long long wait = 0;
                    if (current_time % 24 > tour_start) {
                        wait = 24 - (current_time % 24) + tour_start;
                    } else if (current_time % 24 < tour_start) {
                        wait = tour_start - (current_time % 24);
                    }
                    
                    long long new_time = current_time + wait + D[i];
                    int new_camp = E[i];
                    
                    int new_mask = mask | (1 << i);
                    dp[new_mask][new_camp] = min(dp[new_mask][new_camp], new_time);
                }
            }
        }
        
        // Find minimum time to return to camp 1 after all tours
        long long ans = dp[full_mask][1];
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    
    return 0;
}
