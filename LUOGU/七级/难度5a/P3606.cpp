#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, k;
    cin >> n >> k;
    
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Binary search on total time
    long long low = 1, high = 1e18;
    long long answer = high;
    
    while (low <= high) {
        long long mid = (low + high) / 2;
        
        // Check if we can complete in mid time
        long long total_cows = 0;
        for (int i = 0; i < n; i++) {
            // Minimum cows needed for floor i
            long long needed = (a[i] + mid - 1) / mid;
            total_cows += needed;
        }
        
        if (total_cows <= k) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    
    cout << answer << "\n";
    return 0;
}
