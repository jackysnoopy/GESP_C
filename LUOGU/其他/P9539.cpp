#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l, r;
    string s;
    cin >> n >> l >> r >> s;
    // Construct string with similarity in [l,r], lexicographically smallest
    // similarity = number of positions where result[i]==s[i]
    // Strategy: try to make result[i]='a' always (lex smallest)
    // If s[i]=='a', that counts as a match. Otherwise it doesn't.
    // Count how many 'a' in s: matches_a
    // If matches_a in [l,r]: output all 'a'
    // If matches_a > r: need to reduce matches. Change some 'a' to 'b' at end.
    // If matches_a < l: need more matches. Change some non-'a' to match s.
    int matches_a = 0;
    for (char c : s) if (c == 'a') matches_a++;
    string result(n, 'a');
    if (matches_a >= l && matches_a <= r) {
        cout << result << "\n";
    } else if (matches_a > r) {
        // Need to reduce matches by changing some 'a' positions to 'b'
        int need = matches_a - r;
        for (int i = n-1; i >= 0 && need > 0; i--) {
            if (s[i] == 'a') {
                result[i] = 'b';
                need--;
            }
        }
        cout << result << "\n";
    } else {
        // matches_a < l, need more matches
        int need = l - matches_a;
        // Change some non-'a' positions to match s[i]
        // For lex smallest, change the rightmost positions
        for (int i = n-1; i >= 0 && need > 0; i--) {
            if (s[i] != 'a') {
                result[i] = s[i];
                need--;
            }
        }
        cout << result << "\n";
    }
    return 0;
}
