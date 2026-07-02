#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    
    string s;
    cin >> s;
    
    // Precompute prefix sums
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + (s[i] == '1' ? 1 : -1);
    }
    
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--; r--;
        
        // Find longest good subsequence
        int zeros = 0, ones = 0;
        for (int j = l; j <= r; j++) {
            if (s[j] == '0') zeros++;
            else ones++;
        }
        
        // Good subsequence must have ones >= zeros
        // and prefix condition
        int ans = -1;
        if (ones > zeros) {
            ans = 2 * zeros + 1;
        } else if (ones == zeros) {
            ans = 2 * ones;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}