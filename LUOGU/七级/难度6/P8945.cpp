#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Count zeros and ones
    int zeros = 0;
    for (int x : a) {
        if (x == 0) zeros++;
    }
    
    // Fill k ones into zeros
    int filled = min(k, zeros);
    
    // Calculate maximum subarray sum
    long long max_sum = 0;
    long long current = 0;
    
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) {
            if (filled > 0) {
                current += 1;
                filled--;
            } else {
                current += -1;
            }
        } else if (a[i] == 1) {
            current += 1;
        } else {
            current += -1;
        }
        
        max_sum = max(max_sum, current);
        if (current < 0) current = 0;
    }
    
    cout << max_sum << endl;
    
    return 0;
}