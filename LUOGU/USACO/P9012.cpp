#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        int n = s.size();
        if (n < 3) { cout << -1 << "\n"; continue; }
        int ans = 1000000000;
        // Try all 3 positions for M,O,O in original string
        // For each pair (i,j,k) with i<j<k, cost = ops to make s[i]='M',s[j]='O',s[k]='O'
        // plus deletions of chars outside [i,k]
        // Cost = (i changes) + (k-i+1 changes inside) + (n-1-k deletions) + (i deletions)
        // = n - 3 + changes_needed for choosing positions i,j,k
        // changes = (s[i]!='M') + (s[j]!='O') + (s[k]!='O')
        for (int i = 0; i < n-2; i++) {
            for (int k = i+2; k < n; k++) {
                int j = k - 1; // O at k-1, O at k
                // Actually: M at i, O at j, O at k where j = k-1
                // Or M at i, O at some j, O at k where j can be anything between
                // For MOO: M at i, O at k-1, O at k
                int changes = (s[i] != 'M') + (s[k-1] != 'O') + (s[k] != 'O');
                int cost = changes + (n - 3); // n-3 deletions to remove other chars
                ans = min(ans, cost);
            }
        }
        cout << (ans >= 1000000000 ? -1 : ans) << "\n";
    }
    return 0;
}
