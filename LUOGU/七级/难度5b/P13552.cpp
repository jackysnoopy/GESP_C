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
        int n, k;
        cin >> n >> k;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // We need to perform n-1 operations: exactly n-k operations of type 1 (AND)
        // and k-1 operations of type 2 (addition)
        // Type 1: x AND y -> new number
        // Type 2: x + y -> new number
        
        // Goal: maximize final number
        
        // Key insight: AND reduces bits, addition can increase value
        // With n-k AND operations and k-1 additions:
        // AND operations merge pairs, reducing to k groups
        // Then additions combine the k groups
        
        // Strategy for k=2: 
        // Use 1 AND to combine n-2 numbers (reduce to 2 numbers)
        // Then 1 addition to combine them
        
        // General: AND operations create k "clusters", then additions combine
        
        // Greedy: try to keep high bits
        long long result = 0;
        
        if (k == n) {
            // All additions: just sum everything
            result = 0;
            for (int x : a) result += x;
        } else if (k == 1) {
            // All AND: AND everything together
            result = a[0];
            for (int i = 1; i < n; i++) result &= a[i];
        } else {
            // Mixed: use DP or greedy
            // For simplicity, try different partitions
            // AND some subsets, then add the results
            
            // Try: partition into k groups, AND each group, then sum
            // For small n, try all partitions
            // For large n, greedy approach
            
            // Greedy: try all subsets for AND groups
            // This is exponential but works for small n
            
            if (n <= 20) {
                // DP over subsets
                int full = (1 << n) - 1;
                vector<long long> andVal(1 << n, -1);
                
                for (int mask = 1; mask <= full; mask++) {
                    // Find first set bit
                    int lb = __builtin_ctz(mask);
                    int rest = mask ^ (1 << lb);
                    if (rest == 0) {
                        andVal[mask] = a[lb];
                    } else {
                        andVal[mask] = andVal[rest] & a[lb];
                    }
                }
                
                // DP: dp[mask][j] = max sum using j groups for subset mask
                // Simplified: try all ways to partition into k groups
                result = 0;
                
                // For small n and small k, brute force
                vector<int> groups;
                function<void(int, int)> solve = [&](int pos, int groupsLeft) {
                    if (groupsLeft == 0) {
                        if (pos == full) {
                            // All elements assigned
                        }
                        return;
                    }
                    // Try all subsets of remaining elements
                    int remaining = full ^ pos;
                    for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
                        groups.push_back(sub);
                        solve(pos | sub, groupsLeft - 1);
                        groups.pop_back();
                    }
                };
                
                // Simpler: enumerate all k-partitions
                vector<int> assignment(n, 0);
                function<void(int, int)> assign = [&](int idx, int maxGroup) {
                    if (idx == n) {
                        // Compute AND for each group, then sum
                        long long total = 0;
                        for (int g = 0; g <= maxGroup; g++) {
                            long long gand = -1;
                            bool found = false;
                            for (int i = 0; i < n; i++) {
                                if (assignment[i] == g) {
                                    if (!found) { gand = a[i]; found = true; }
                                    else gand &= a[i];
                                }
                            }
                            if (found) total += gand;
                        }
                        result = max(result, total);
                        return;
                    }
                    for (int g = 0; g <= min(maxGroup + 1, k - 1); g++) {
                        assignment[idx] = g;
                        assign(idx + 1, max(g, maxGroup));
                    }
                };
                
                assign(0, -1);
            } else {
                // For large n: greedy approach
                // Sort by bit count, try to group similar numbers
                
                // Simple heuristic: AND all, then add with best remaining
                long long andAll = a[0];
                for (int i = 1; i < n; i++) andAll &= a[i];
                
                // Try partitioning into k groups
                // Use k-1 additions to combine k AND-results
                // Best: put one element per group for k-1 groups, AND rest
                
                result = 0;
                // Try putting each of the largest elements as individual groups
                vector<int> sorted_a = a;
                sort(sorted_a.begin(), sorted_a.end(), greater<int>());
                
                // Greedy: take k-1 largest as individual, AND rest
                long long sum = 0;
                for (int i = 0; i < k - 1 && i < n; i++) {
                    sum += sorted_a[i];
                }
                long long andRest = sorted_a[k - 1];
                for (int i = k; i < n; i++) {
                    andRest &= sorted_a[i];
                }
                sum += andRest;
                result = max(result, sum);
            }
        }
        
        cout << result << "\n";
    }
    
    return 0;
}