#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    long long K;
    cin >> N >> K;
    
    vector<long long> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    
    // Binary search on capacity c
    // For each c, check if we can sort with K spare gems
    
    // Brute force for small N
    // For larger N, need smarter approach
    
    // The problem is about stack-sortable permutations
    // With capacity c, we can handle permutations with certain properties
    
    // For now, brute force
    int lo = 0, hi = N;
    int ans = N;
    
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        
        // Check if capacity mid is enough
        // Simulate with stack of capacity mid
        
        // Simple check: count inversions
        // With K gems, we can reduce some a[i] to 0 and set them to optimal values
        
        // For now, assume capacity = N-1 is always enough
        // and capacity = 0 is only enough if already sorted
        
        bool sorted = true;
        for (int i = 1; i < N; i++) {
            if (a[i] < a[i-1]) {
                sorted = false;
                break;
            }
        }
        
        if (sorted) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    // Simplified: output minimum capacity
    // For actual solution, need stack-sortability analysis
    
    // Count minimum stack depth needed
    int depth = 0;
    int maxDepth = 0;
    vector<int> stk;
    
    for (int i = 0; i < N; i++) {
        while (!stk.empty() && stk.back() > a[i]) {
            stk.pop_back();
            depth--;
        }
        stk.push_back(a[i]);
        depth++;
        maxDepth = max(maxDepth, depth);
    }
    
    cout << max(0, maxDepth - 1) << "\n";
    return 0;
}
