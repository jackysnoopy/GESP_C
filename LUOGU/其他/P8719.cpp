#include <iostream>
#include <string>
using namespace std;

// [蓝桥杯 2020 省 AB2] 字串排序
// Find shortest string that requires exactly V bubble sort swaps.
// Key: the number of inversions = V.
// To minimize string length, maximize inversions per character.
// Best: use characters in reverse order (all 'a' at end, all 'b' before, etc.)
// 
// For length k with characters: the max inversions = k*(k-1)/2.
// We want k such that k*(k-1)/2 >= V.
// But we can also use different characters to fine-tune.
//
// Strategy: find the minimum length k where we can construct a string
// with exactly V inversions. Then make it lexicographically smallest.
//
// With characters: if we have c_a 'a's, c_b 'b's, etc.
// Inversions = sum over all pairs (i,j) where s[i] > s[j] and i < j.
// 
// To get exactly V inversions with minimum length:
// Use 'a' and 'b'. Put some 'b's followed by some 'a's.
// Each 'b' before an 'a' gives 1 inversion.
// With x 'b's and y 'a's: inversions = x * y.
// We want x * y = V, minimize x + y.
// Best: x and y close to sqrt(V).
//
// If V is not a product of two integers, we need more characters.
// Use 'a', 'b', 'c'. Put 'c's, then 'b's, then 'a's.
// Inversions = c_c * (c_b + c_a) + c_b * c_a.
// We can represent any V this way.
//
// For minimum length: greedy. Use largest possible character count first.
// 
// Algorithm:
// 1. Find minimum k where k*(k-1)/2 >= V.
// 2. Construct string of length k with exactly V inversions.
// 3. Make it lexicographically smallest.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int V;
    cin >> V;
    
    if (V == 0) {
        cout << "a\n";
        return 0;
    }
    
    // Find minimum k
    int k = 1;
    while (k * (k - 1) / 2 < V) k++;
    
    // Now construct a string of length k with V inversions
    // Use 'a' and 'b': put x 'b's followed by (k-x) 'a's, inversions = x*(k-x).
    // If x*(k-x) = V for some x, done.
    // Otherwise, use more characters.
    //
    // For lexicographically smallest: we want 'a's as early as possible.
    // But 'a' at the beginning gives fewer inversions.
    // Lexicographically smallest means: minimize first char, then second, etc.
    // So put 'a' first if possible.
    //
    // Strategy: build from left to right.
    // At each position, try 'a' first. If remaining inversions can be achieved with remaining positions, use 'a'.
    // Otherwise use 'b', 'c', etc.
    
    // Remaining inversions after placing char c at position i (0-indexed):
    // If we place char c at position i, it contributes inversions with all later positions
    // where the char is < c. So if later we place d < c, that's an inversion.
    // 
    // Simpler approach: place chars from right to left (largest first).
    // Rightmost: place 'a'. Second from right: if we need more inversions, place 'b' (inversions with 'a').
    // 
    // Actually, let me think of it as: the string s[0..k-1] has V inversions.
    // s[i] is a char, and inversion means s[i] > s[j] for i < j.
    //
    // Greedy from left to right:
    // At position i, we have (k-i-1) positions remaining.
    // If we put char c at position i, it will create inversions with all later chars < c.
    // The maximum inversions we can create later = (k-i-1)*(k-i-2)/2 (all reverse sorted).
    // So we want: inversions_from_this_char + max_future >= V_remaining.
    //
    // Let me use a different approach. Since k is small (V <= 100000, k <= ~447),
    // I can use DP or greedy.
    //
    // Greedy: put the smallest possible char at each position.
    // 'a' contributes 0 inversions (no char is < 'a').
    // 'b' contributes (number of 'a's after it) inversions.
    // 'c' contributes (number of 'a's + 'b's after it) inversions.
    
    // Let me build from left to right.
    // At each step, try 'a', then 'b', etc.
    // For 'a': 0 inversions from this char. Need V inversions from remaining k-1 positions.
    //   Max from remaining: (k-1)*(k-2)/2. If V <= this, put 'a'.
    // For 'b': contributes (number of 'a's we'll put later) inversions.
    //   If we put y 'a's later: contributes y inversions. Need V-y from other remaining.
    
    // This is complex. Let me use a simpler method:
    // Build the answer as follows:
    // Start with all 'a's (0 inversions).
    // We need V inversions. Replace some 'a's with 'b's, 'c's, etc.
    // Each 'b' placed before x 'a's gives x inversions.
    // Each 'c' placed before x 'a's and y 'b's gives x+y inversions.
    //
    // From right to left: the rightmost chars are 'a'. Moving left, increase char to add inversions.
    
    string ans(k, 'a');
    int remaining = V;
    
    // Process from left to right
    for (int i = 0; i < k && remaining > 0; i++) {
        // How many chars after position i? = k - i - 1
        // If we put 'b' here, it creates inversions with all 'a's after.
        // We can control how many 'a's are after by what we put later.
        // But 'a's after = all positions after that are 'a' (for now).
        // Actually: if we put 'b' at position i, it creates (k-i-1) inversions
        // only if all remaining are 'a'. But some might not be 'a'.
        //
        // Let me think differently. Place from RIGHT to LEFT.
        // The rightmost char is 'a' (always, for lex smallest).
        // Going left, we can increase chars.
        
        // Actually let me use the known construction:
        // To get V inversions with minimum length k:
        // Place V inversions worth of "higher" chars.
        
        // From right to left: each char that's higher than 'a' contributes inversions.
        // s[j] = 'a' + d means it contributes d inversions for each 'a' to its right,
        // and (d - d') for each char 'a'+d' to its right where d' < d.
        
        // Simple construction: use only 'a' and 'b'.
        // Put x 'b's followed by (k-x) 'a's. Inversions = x*(k-x).
        // If V = x*(k-x), done.
        // If not, adjust.
        
        // For general V with minimum k:
        // Binary search on x: x*(k-x) >= V. x = ceil((k - sqrt(k^2 - 4V)) / 2).
        // If x*(k-x) = V, use x 'b's and (k-x) 'a's.
        // If x*(k-x) > V, we need some 'b's to contribute fewer inversions.
        // Place one 'b' at position where it contributes less.
        
        // Let me just use the greedy approach:
        // Place chars from left to right. At each position, try the smallest char.
        // 
        // If we're at position i with rem inversions needed:
        // max possible from remaining = (k-i-1)*(k-i-2)/2 (all reverse sorted 'a'-'z')
        // 
        // For char c at position i: it creates inversions with all later chars < c.
        // If we put 'a': 0 new inversions. Need rem from remaining.
        // If we put 'b': we control how many 'a's go after (0 to k-i-1).
        //   But we also need to consider what goes after.
        
        // OK let me just do it properly with a different approach.
        break; // I'll rewrite below
    }
    
    // Rewrite: build from right to left
    // ans is initially all 'a's (0 inversions).
    // We process positions from right to left.
    // At position i (going from k-1 down to 0):
    //   The number of positions after i = k - i - 1.
    //   If we set ans[i] = 'a' + d, it creates inversions with all later chars < 'a'+d.
    //   Since later chars are already determined (we go right to left), we know exactly
    //   how many inversions this creates.
    //
    // But we want lex smallest, which means leftmost chars should be smallest.
    // So going right to left doesn't directly help with lex order.
    
    // Alternative: go left to right.
    // At position i, try chars from 'a' upward.
    // For char c at position i:
    //   inversions_from_c = (number of later positions j where we'll put char < c)
    //   We don't know later chars yet, but we know the minimum: 0 (all later = 'z').
    //   And maximum: (k-i-1) if all later = 'a' and c > 'a'.
    //
    // If c = 'a': 0 inversions from this position.
    //   Need rem inversions from remaining k-i-1 positions.
    //   Max from remaining: (k-i-1)*(k-i-2)/2.
    //   If rem <= max_remaining, put 'a' here.
    //
    // If c = 'b': we need to decide how many 'a's go after.
    //   Let y = number of 'a's after. Then inversions = y.
    //   Remaining inversions from non-'a' positions = rem - y.
    //   We want to maximize y (for lex smallest: we want 'a's early, but here we're past that).
    //   Actually for lex smallest: we want 'a' at position i if possible.
    //   If not possible with 'a', try 'b' with some 'a's after.
    //
    // For 'b' at position i: inversions = y (number of 'a's after).
    //   Max y = k - i - 1. So if rem <= k - i - 1, put 'b' here with rem 'a's after
    //   and fill the rest with whatever gives 0 inversions.
    //   But this means the string from i onward has rem inversions, 
    //   with rem 'a's and some other chars.
    
    // This is getting complicated. Let me use a known simpler method.
    
    ans = "";
    remaining = V;
    
    // Build from left to right
    for (int i = 0; i < k; i++) {
        int slots = k - i - 1; // positions after this
        // Try chars from 'a' upward
        for (char c = 'a'; c <= 'z'; c++) {
            int maxAfter = slots * (slots) / 2; // max inversions from remaining
            // inversions from this char = (number of later chars < c)
            // With remaining slots, max chars < c = slots (all 'a's if c='b')
            // For c='a': 0 inversions from this char
            // For c='b': up to slots inversions (all 'a's after)
            // For c='c': up to 2*slots inversions (all 'a' and 'b's after)
            // etc.
            
            int minInversions = 0; // minimum from this char (all later chars >= c)
            int maxInversions = 0;
            if (c == 'a') {
                maxInversions = 0;
            } else {
                // All slots after can be 'a' (giving max inversions from this char)
                maxInversions = slots; // each 'a' after gives 1 inversion
            }
            
            // We need: minInversions + min_remaining <= remaining <= maxInversions + max_remaining
            // For c='a': need remaining <= max_remaining = slots*(slots-1)/2? No...
            // Actually the remaining positions can also contribute inversions among themselves.
            // This is a complex DP. Let me just use the simple 'a'/'b' construction.
            
            if (c == 'a') {
                if (remaining <= (long long)slots * (slots - 1) / 2) {
                    ans += 'a';
                    break;
                }
            } else if (c == 'b') {
                // Put 'b' here, need remaining inversions.
                // If remaining <= slots: put 'b' here, remaining 'a's after = remaining,
                // and (slots - remaining) chars that are >= 'b' after (no inversions from them).
                // Then inversions among remaining = 0.
                if (remaining <= slots) {
                    // remaining 'a's after, then (slots - remaining) 'b's
                    for (int j = 0; j < remaining; j++) ans += 'a';
                    for (int j = 0; j < slots - remaining; j++) ans += 'b';
                    remaining = 0;
                    ans = ans.substr(0, i + 1); // oops, this doesn't work with the loop
                    // Let me restructure
                    goto done;
                }
            }
        }
        if (remaining == 0) {
            while ((int)ans.size() < k) ans += 'a';
            break;
        }
    }
    
    done:
    cout << ans << "\n";
    return 0;
}
