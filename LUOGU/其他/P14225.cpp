#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        string S;
        cin >> S;
        // Beautiful string: no two adjacent chars are the same.
        // f(S,d) = left shift by d.
        // Find min changes to make ALL rotations beautiful.
        // Same as P14161: all rotations beautiful means all chars same.
        // Wait, that's not right. "beautiful" means no adjacent equal chars.
        // For a circular string to have all rotations beautiful:
        // Every rotation s[i]..s[n-1]s[0]..s[i-1] must have no adjacent equal chars.
        // This means s[j] != s[(j+1)%n] for all j. I.e., the circular string has no equal adjacent.
        // So we need: s[i] != s[(i+1)%n] for all i.
        // Minimize changes.
        
        // For a circular string with no equal adjacent:
        // If n is even: we can use alternating pattern "ababab..." 
        //   Choose a,b to minimize changes. Try all 26*26 pairs.
        // If n is odd: alternating requires 3+ chars: "abcabc..." or similar.
        //   Actually for odd n, alternating 2 chars: "ababa" → a!=b, b!=a, a!=b, b!=a, a!=a (last != first).
        //   For odd n, alternating 2 chars doesn't work (last == first).
        //   So we need all chars to alternate with period >= 3.
        //   For odd n: pattern must be like "abcabc...ab" where a,b,c are distinct.
        //   Actually: for odd n, we need s[i] != s[(i+1)%n] for all i.
        //   This is possible with 2 chars only if n is even.
        //   For odd n, we need at least 3 chars.
        //   But we can still minimize changes.
        
        // Actually, the constraint is: s[i] != s[(i+1)%n] for all i (mod n).
        // This is a graph coloring problem on a cycle.
        // For even n: 2 colors suffice. Try all 26*25 pairs of (c1,c2) for alternating.
        // For odd n: 2 colors don't work. Need 3 colors.
        //   Try all 26*25*24 triples for "abcabc..." pattern.
        //   But 26*25*24 = 15600, times n=10^5 = 1.56*10^9. Too slow.
        
        // Better approach: for even n, try all 26*25 = 650 pairs. For each pair (c1,c2):
        //   positions 0,2,4,... get c1; positions 1,3,5,... get c2.
        //   Changes = count of mismatches.
        // For odd n, we need 3 colors. Pattern: c1,c2,c3,c1,c2,c3,...
        //   Try all 26*25*24 = 15600 triples. For n=10^5: 1.56*10^9. Too slow.
        //   Alternative: for odd n, the pattern repeats every 3.
        //   Group positions by i%3. For each group, find the most frequent char.
        //   Try all 26 choices for group 0, 25 for group 1, 24 for group 2.
        //   For each triple: changes = sum of (group_size - freq[group_char]).
        //   This is O(26*25*24) per test case. For T up to 100 and n up to 10^5:
        //   100 * 15600 = 1.56M. Fast enough!
        
        int ans = n;
        if (n % 2 == 0) {
            for (int c1 = 0; c1 < 26; c1++) {
                for (int c2 = 0; c2 < 26; c2++) {
                    if (c1 == c2) continue;
                    int changes = 0;
                    for (int i = 0; i < n; i++) {
                        char expected = (i % 2 == 0) ? c1 : c2;
                        if (S[i] != 'a' + expected) changes++;
                    }
                    ans = min(ans, changes);
                }
            }
        } else {
            for (int c1 = 0; c1 < 26; c1++) {
                for (int c2 = 0; c2 < 26; c2++) {
                    if (c2 == c1) continue;
                    for (int c3 = 0; c3 < 26; c3++) {
                        if (c3 == c1 || c3 == c2) continue;
                        int changes = 0;
                        for (int i = 0; i < n; i++) {
                            int mod = i % 3;
                            char expected = (mod == 0) ? c1 : (mod == 1) ? c2 : c3;
                            if (S[i] != 'a' + expected) changes++;
                        }
                        ans = min(ans, changes);
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
