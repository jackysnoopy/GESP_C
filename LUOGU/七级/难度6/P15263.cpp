#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, C;
    cin >> n >> C;
    
    vector<int> pos(n);
    for (int i = 0; i < n; i++) cin >> pos[i];
    
    // For each k from 1 to N/2, find the maximum minimum distance
    // Binary search on distance d, check if we can select k pairs with min distance >= d
    
    int maxK = n / 2;
    
    for (int k = 1; k <= maxK; k++) {
        // Binary search on distance
        int lo = 0, hi = C / 2;
        int ans = 0;
        
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            
            // Check if we can select k pairs with min circular distance >= mid
            // Break the circle and use greedy
            
            // For circular problem, try each starting point
            bool found = false;
            
            for (int start = 0; start < n && !found; start++) {
                // Try pairing from position start
                vector<int> used(n, 0);
                int paired = 0;
                
                // Simple greedy: pair consecutive with distance >= mid
                int last = -1;
                for (int i = 0; i < n && paired < k; i++) {
                    int idx = (start + i) % n;
                    if (used[idx]) continue;
                    
                    // Find next unpaired with distance >= mid
                    for (int j = i + 1; j < n && paired < k; j++) {
                        int jdx = (start + j) % n;
                        if (used[jdx]) continue;
                        
                        // Calculate circular distance
                        int d = abs(pos[idx] - pos[jdx]);
                        d = min(d, C - d);
                        
                        if (d >= mid) {
                            used[idx] = 1;
                            used[jdx] = 1;
                            paired++;
                            break;
                        }
                    }
                }
                
                if (paired >= k) found = true;
            }
            
            if (found) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        
        cout << ans << (k < maxK ? " " : "\n");
    }
    
    return 0;
}
