#include <iostream>
#include <string>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string S, D;
    cin >> S >> D;
    int si = 0;
    for (int i = 0; i < (int)D.size(); i++) {
        if (si < (int)S.size() && D[i] == S[si]) si++;
    }
    if (si < (int)S.size()) { cout << -1 << "\n"; return 0; }
    // Find minimum ending position
    // Re-scan: greedily match, then try to shorten from end
    int ans = -1;
    // Try all possible ending positions
    for (int end = 0; end < (int)D.size(); end++) {
        // Check if S is subsequence of D[0..end]
        int si2 = 0;
        for (int i = 0; i <= end; i++) {
            if (si2 < (int)S.size() && D[i] == S[si2]) si2++;
        }
        if (si2 == (int)S.size()) { ans = end + 1; break; }
    }
    cout << ans << "\n";
    return 0;
}
