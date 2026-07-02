#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // We want to make all elements distinct using minimum number of addition operations
    // Each operation adds x to a subarray [l, r]
    
    // Key insight: count the frequency of each value
    // For each value that appears k times, we need at least k-1 operations to make them distinct
    // But operations can affect multiple elements, so we can do better
    
    // Count frequencies
    vector<long long> sorted_a = a;
    sort(sorted_a.begin(), sorted_a.end());
    
    // Count duplicates
    int duplicates = 0;
    for (int i = 1; i < n; i++) {
        if (sorted_a[i] == sorted_a[i-1]) {
            duplicates++;
        }
    }
    
    // Each operation can fix at most one duplicate
    // So the answer is at least the number of duplicates
    
    // But we can also use operations to shift entire ranges
    // The minimum number of operations is the number of duplicates
    
    cout << duplicates << endl;
    
    return 0;
}
