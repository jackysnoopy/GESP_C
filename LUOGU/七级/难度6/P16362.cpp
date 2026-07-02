#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> x(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    
    // Check if array is already sorted
    bool sorted = true;
    for (int i = 1; i < n; i++) {
        if (x[i] < x[i-1]) {
            sorted = false;
            break;
        }
    }
    
    // Precompute: for each position, is prefix [0..i] sorted?
    vector<bool> prefixSorted(n, true);
    for (int i = 1; i < n; i++) {
        prefixSorted[i] = prefixSorted[i-1] && (x[i] >= x[i-1]);
    }
    
    // Precompute: for each position, is suffix [i..n-1] sorted?
    vector<bool> suffixSorted(n, true);
    for (int i = n-2; i >= 0; i--) {
        suffixSorted[i] = suffixSorted[i+1] && (x[i] <= x[i+1]);
    }
    
    // For each query (a, b):
    // Operation 1: sort first a elements
    // Operation 2: sort last b elements
    // After operations, array should be sorted
    
    // If a + b >= n, one operation is enough (sort first a, then sort last b)
    // Actually, if a + b >= n, sorting first a then last b covers all elements
    
    while (q--) {
        int a, b;
        cin >> a >> b;
        
        if (sorted) {
            cout << "0\n";
            continue;
        }
        
        // Check if one operation suffices
        // Sort first a: after this, prefix [0..a-1] is sorted
        // Sort last b: after this, suffix [n-b..n-1] is sorted
        
        // Check if a + b >= n
        if (a + b >= n) {
            cout << "1\n";
            continue;
        }
        
        // Check if sorting first a makes the whole array sorted
        // After sorting first a, we need suffix [a..n-1] to be sorted
        // AND x[a-1] <= x[a]
        
        bool oneOp = false;
        
        // Check sort first a
        if (suffixSorted[a]) {
            // Check if x[a-1] <= x[a] after sorting
            // Actually we need to check if the sorted prefix connects to suffix
            // Find max in sorted prefix and min in suffix
            vector<int> prefix(x.begin(), x.begin() + a);
            sort(prefix.begin(), prefix.end());
            if (prefix.back() <= x[a]) {
                oneOp = true;
            }
        }
        
        // Check sort last b
        if (!oneOp && prefixSorted[n-b-1]) {
            vector<int> suffix(x.begin() + n - b, x.end());
            sort(suffix.begin(), suffix.end());
            if (x[n-b-1] <= suffix.front()) {
                oneOp = true;
            }
        }
        
        if (oneOp) {
            cout << "1\n";
            continue;
        }
        
        // Check if two operations suffice
        // Sort first a, then sort last b
        // After both operations, array should be sorted
        
        vector<int> temp = x;
        sort(temp.begin(), temp.begin() + a);
        sort(temp.end() - b, temp.end());
        
        bool twoOps = true;
        for (int i = 1; i < n; i++) {
            if (temp[i] < temp[i-1]) {
                twoOps = false;
                break;
            }
        }
        
        if (twoOps) {
            cout << "2\n";
        } else {
            cout << "-1\n";
        }
    }
    
    return 0;
}
