#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> L(q), R(q), A(q);
    for (int i = 0; i < q; i++) {
        cin >> L[i] >> R[i] >> A[i];
    }
    
    // We need to construct a permutation of 0 to n-1
    // such that for each query (L, R, A), the minimum element in [L, R] is A
    
    // This means:
    // 1. A must be in position [L, R]
    // 2. All elements in [L, R] must be >= A
    // 3. A is the minimum in [L, R]
    
    // Let's use a greedy approach:
    // For each position, determine the range of possible values
    
    // Initialize: each position can have any value from 0 to n-1
    vector<int> result(n, -1);
    
    // Process queries in order of A (smallest first)
    vector<int> order(q);
    for (int i = 0; i < q; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) {
        return A[i] < A[j];
    });
    
    for (int idx : order) {
        int l = L[idx], r = R[idx], a = A[idx];
        
        // Check if a is already placed in [l, r]
        bool found = false;
        for (int i = l; i <= r; i++) {
            if (result[i] == a) {
                found = true;
                break;
            }
        }
        
        if (!found) {
            // Place a in the first available position in [l, r]
            for (int i = l; i <= r; i++) {
                if (result[i] == -1) {
                    result[i] = a;
                    found = true;
                    break;
                }
            }
        }
        
        if (!found) {
            // Can't satisfy this query
            cout << -1;
            for (int i = 1; i < n; i++) cout << " " << -1;
            cout << endl;
            return 0;
        }
    }
    
    // Fill remaining positions with unused values
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++) {
        if (result[i] != -1) {
            used[result[i]] = true;
        }
    }
    
    int ptr = 0;
    for (int i = 0; i < n; i++) {
        if (result[i] == -1) {
            while (used[ptr]) ptr++;
            result[i] = ptr;
            used[ptr] = true;
        }
    }
    
    // Output result
    for (int i = 0; i < n; i++) {
        cout << result[i] << (i < n - 1 ? " " : "\n");
    }
    
    return 0;
}
