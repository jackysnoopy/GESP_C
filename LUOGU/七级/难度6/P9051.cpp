#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    
    // Binary search on answer
    long long low = -1e18, high = 1e18;
    
    while (low < high) {
        long long mid = (low + high) / 2;
        
        // Check if we can achieve max subarray sum <= mid
        // Using greedy with k selections
        int used = 0;
        long long current = 0;
        long long max_current = 0;
        
        for (int i = 0; i < n; i++) {
            long long val = (used < k) ? a[i] : b[i];
            
            current = max(val, current + val);
            max_current = max(max_current, current);
            
            if (max_current > mid) {
                // Need to use a[i] instead of b[i]
                if (used < k) {
                    used++;
                    current = max(a[i], (long long)a[i]);
                    max_current = max(max_current, current);
                }
            }
        }
        
        if (max_current <= mid) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    
    cout << low << endl;
    
    // Output assignment
    string s(n, 'B');
    int used = 0;
    
    for (int i = 0; i < n; i++) {
        if (used < k && a[i] > b[i]) {
            s[i] = 'A';
            used++;
        }
    }
    
    cout << s << endl;
    
    return 0;
}