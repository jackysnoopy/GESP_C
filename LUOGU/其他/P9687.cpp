#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n, p;
        cin >> n >> p;
        // Count interior 0s with both neighbors 1 = p
        // Lexicographically smallest
        // Each such pattern "101" contributes 1 to p
        // To minimize lex order: put 0s as left as possible
        // Pattern: 0010101...01
        // Interior 0s with both 1 neighbors: only full "101" patterns count
        // Need exactly p such patterns
        // Build: 00 + p*"10" + remaining 0s
        // But "101" patterns: if we have "...10101...", each 0 between two 1s counts.
        // "101" has 1 interior 0. "10101" has 2 interior 0s.
        // So p interior 0s = p+1 ones with p zeros between them, but also zeros outside.
        // 
        // Construct: zeros at start, then alternating 1,0 pattern
        // 0...0 1 0 1 0 ... 1 (p+1 ones, p zeros between)
        // Interior 0 count = p if zeros between are the only interior 0s with 1 on both sides
        // But first 0 in the alternating section has 1 on right but what on left?
        // If preceded by 0, it's not counted. Good.
        // Last 0 has 1 on right but nothing on left... it's 0.
        // 
        // Actually let's think: string like 0010101
        // Position 2 (0-indexed): 1, not 0
        // Position 3: 0, neighbors 1 and 0. Not both 1.
        // Hmm that doesn't work.
        // 
        // Pattern "00101": positions: 0,0,1,0,1
        // Interior 0s: pos 1 (neighbors 0,1 - not both 1), pos 3 (neighbors 1,1 - yes!)
        // So 1 interior 0 with both 1 neighbors. p=1, n=5. Output: 00101. Matches sample!
        // 
        // For p=1, n=3: "101". Interior: pos 1 (neighbors 1,1). p=1. But output is "101"? 
        // Wait sample says n=3,p=1 -> "101". Yes!
        // 
        // General: "1" + "01" * p = 1010101...1 (length 2p+1)
        // But we need lex smallest. Put zeros at front.
        // Prepend zeros: if total length > 2p+1, add zeros at front.
        // Interior 0s with both 1 neighbors: still p (the zeros between 1s).
        // Zeros at front don't have 1 on left, so not counted.
        // 
        // But wait: what if n is between p+1 and 2p+1?
        // Minimum length for p interior 0s: need at least p+1 chars for p zeros and 1 one... 
        // Actually minimum is 2p+1? No: "101" = 3 chars for p=1. 
        // "10101" = 5 for p=2. Pattern: 10 repeated p times + 1 = 2p+1.
        // But we can have trailing zeros too.
        // 
        // Wait for p=1: "101" (3) or "0101" (4) - but "0101" interior: pos 1 (0, neighbors 1,0 - no),
        // pos 2 (1, not 0). Hmm.
        // Actually "0101": 0,1,0,1. Interior: pos 1 (1, not 0), pos 2 (0, neighbors 1,1 - yes!).
        // So "0101" also has p=1. And "00101" has p=1 too.
        // 
        // For lex smallest: start with as many 0s as possible.
        // But we can't have too many leading 0s or we won't have enough room.
        // 
        // Minimum pattern: "101" (length 3, p=1), "10101" (length 5, p=2)
        // Add leading zeros: n - (2p+1) zeros at front.
        // But need n >= 2p+1 for this to work? 
        // Actually for p=1, "00101" works (n=5). "000101" (n=6) also works.
        // What about n=4, p=1? "0101" works! That's only 4 chars.
        // 
        // Hmm, so minimum length is p+2? "0" + "10" * p = 01010... length p*2+1... no.
        // Let me reconsider. For p interior 0s:
        // We need p+1 ones (forming p gaps), and zeros in those gaps.
        // Total minimum: p+1 ones + p zeros between = 2p+1.
        // But we can also have leading/trailing zeros.
        // For n < 2p+1: impossible.
        // For n = 2p+1: "10101...1"
        // For n > 2p+1: prepend zeros.
        // 
        // But sample n=3,p=1: 2*1+1=3=n. "101". Correct!
        // n=5,p=3: 2*3+1=7 > 5. Impossible! Output -1. Correct!
        // n=5,p=4: 2*4+1=9 > 5. Impossible. -1. Correct!
        // n=5,p=5: Impossible. -1. Correct!
        // 
        // So: if n < 2*p+1, output -1.
        // Otherwise: (n-(2*p+1)) zeros + "1" + "01"*p
        if (n < 2 * p + 1) {
            cout << -1 << "\n";
        } else {
            string result = "";
            for (int i = 0; i < n - 2*p - 1; i++) result += "0";
            result += "1";
            for (int i = 0; i < p; i++) result += "01";
            cout << result << "\n";
        }
    }
    return 0;
}
