#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    long long t;
    cin >> n >> k >> t;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // Each stack has the same sequence a[0..n-1]
    // k stacks, total gifts = n * k
    // Each participant can receive at most t different types
    
    // Greedy: count how many distinct types are in each segment of length t*? 
    // Actually: we process gifts in order (stack 1 top-to-bottom, then stack 2, etc.)
    // Each participant takes consecutive gifts until they would exceed t distinct types
    
    // Count total gifts and determine minimum participants
    long long totalGifts = (long long)n * k;
    
    // For each position in the sequence, track distinct types
    // Since all stacks have the same sequence, the total sequence is a repeated k times
    
    // Key: count distinct types in the repeated sequence and partition greedily
    
    // Count distinct types overall
    vector<int> types = a;
    sort(types.begin(), types.end());
    types.erase(unique(types.begin(), types.end()), types.end());
    int totalTypes = types.size();
    
    // If totalTypes <= t, one participant is enough
    if (totalTypes <= t) {
        cout << 1 << "\n";
        return 0;
    }
    
    // Greedy partitioning: scan the k*n sequence, count distinct types per participant
    long long ans = 0;
    long long pos = 0;
    
    while (pos < totalGifts) {
        ans++;
        // Start a new participant
        vector<bool> hasType(1000001, false);
        int distinctCount = 0;
        
        while (pos < totalGifts && distinctCount < t) {
            int type = a[pos % n];
            if (!hasType[type]) {
                if (distinctCount >= t) break;
                hasType[type] = true;
                distinctCount++;
            }
            pos++;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}