#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
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
    
    // Compute LIS length starting from each position
    vector<int> lis_start(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            if (a[j] > a[i]) {
                lis_start[i] = max(lis_start[i], lis_start[j] + 1);
            }
        }
    }
    
    // Find maximum LIS length
    int max_lis = *max_element(lis_start.begin(), lis_start.end());
    
    int m;
    cin >> m;
    
    while (m--) {
        int L;
        cin >> L;
        
        if (L > max_lis) {
            cout << "Impossible\n";
            continue;
        }
        
        // Find lexicographically smallest increasing subsequence of length L
        vector<int> result;
        int last_val = INT_MIN;
        int remaining = L;
        
        for (int i = 0; i < n && remaining > 0; i++) {
            if (a[i] > last_val && lis_start[i] >= remaining) {
                result.push_back(i + 1);
                last_val = a[i];
                remaining--;
            }
        }
        
        for (int i = 0; i < L; i++) {
            cout << result[i] << (i == L - 1 ? "\n" : " ");
        }
    }
    
    return 0;
}
