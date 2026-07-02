#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // We need to find a permutation P such that consecutive elements have different types
    // and P is lexicographically smallest
    
    // Count occurrences of each type
    vector<int> count(n + 1, 0);
    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }
    
    // Check if valid permutation exists
    // A valid permutation exists if and only if no type appears more than (n+1)/2 times
    int max_count = *max_element(count.begin(), count.end());
    if (max_count > (n + 1) / 2) {
        cout << -1 << endl;
        return 0;
    }
    
    // Greedy: always pick the smallest possible element that doesn't conflict
    // Use a priority queue to always pick the most frequent element first
    // But we need lexicographically smallest, so we need to be careful
    
    // Actually, let's use a different approach:
    // For each position, try to place the smallest possible element
    // that doesn't conflict with the previous element
    
    vector<int> result;
    vector<bool> used(n, false);
    
    for (int pos = 0; pos < n; pos++) {
        // Try to place the smallest possible element
        for (int val = 1; val <= n; val++) {
            if (count[val] == 0) continue;
            if (!result.empty() && a[result.back() - 1] == a[val - 1]) continue;
            
            // Check if we can complete the permutation after placing val
            // This is complex, let's just try it
            
            result.push_back(val);
            count[val]--;
            
            // Check if remaining elements can be placed
            int remaining = n - pos - 1;
            int max_remaining = 0;
            for (int v = 1; v <= n; v++) {
                max_remaining = max(max_remaining, count[v]);
            }
            
            if (max_remaining > (remaining + 1) / 2) {
                // Can't complete, undo
                result.pop_back();
                count[val]++;
                continue;
            }
            
            break;
        }
    }
    
    if (result.size() != n) {
        cout << -1 << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << result[i] << (i < n - 1 ? " " : "\n");
        }
    }
    
    return 0;
}
