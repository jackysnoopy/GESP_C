#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n, d;
        cin >> n >> d;
        
        vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        // We want to find the minimum number of cuts to get d equal slices
        // Each cut splits a slice into two
        // After cuts, we need at least d slices of the same size
        
        // For each possible target size, compute the minimum cuts needed
        // The target size must divide some slice
        
        // Let's try all possible target sizes
        // For each slice a[i], the possible target sizes are divisors of a[i]
        
        // For a target size t, the number of slices we can get from a[i] is floor(a[i] / t)
        // The number of cuts needed is (number of slices - 1) if we use all of a[i]
        // But we might not use all of a[i]
        
        // Actually, for a target size t:
        // From slice a[i], we can get floor(a[i] / t) slices of size t
        // The number of cuts needed is floor(a[i] / t) - 1 (if we use all of a[i])
        // But we might want to leave some remainder
        
        // For d slices of size t, we need to find the minimum cuts
        // This is a knapsack-like problem
        
        // Let's try a different approach:
        // For each possible target size t, compute the minimum cuts needed
        
        int ans = d; // Worst case: cut everything
        
        // Try all possible target sizes
        // For each slice a[i], try all divisors of a[i]
        map<long long, int> divisors;
        for (int i = 0; i < n; i++) {
            for (long long j = 1; j * j <= a[i]; j++) {
                if (a[i] % j == 0) {
                    divisors[j]++;
                    if (j != a[i] / j) {
                        divisors[a[i] / j]++;
                    }
                }
            }
        }
        
        for (auto it = divisors.begin(); it != divisors.end(); ++it) {
            long long t = it->first;
            // For target size t, compute the minimum cuts needed
            int total_slices = 0;
            int total_cuts = 0;
            
            for (int i = 0; i < n; i++) {
                int slices = a[i] / t;
                total_slices += slices;
                total_cuts += slices - 1;
            }
            
            if (total_slices >= d) {
                // We have enough slices, but we might need fewer cuts
                // We only need d slices, so we can leave some slices unused
                
                // The minimum cuts is: total_cuts - (total_slices - d)
                // Because we can leave (total_slices - d) slices unused
                // and each unused slice saves one cut
                
                int cuts = total_cuts - (total_slices - d);
                cuts = max(cuts, 0);
                ans = min(ans, cuts);
            }
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    
    return 0;
}
