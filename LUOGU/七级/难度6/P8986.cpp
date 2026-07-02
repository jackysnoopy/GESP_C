#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, l, r;
    cin >> n >> l >> r;
    
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    
    // Simplified approach
    // Find minimum cut length
    int ans = n;
    
    // Try different cut positions
    for (int cut_l = 0; cut_l < l; cut_l++) {
        for (int cut_r = r + 1; cut_r <= n; cut_r++) {
            int len = cut_r - cut_l;
            if (len < ans) {
                ans = len;
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}