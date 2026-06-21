#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
string largestSubseq(const string& s) {
    string res;
    char mx = 0;
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        if (s[i] >= mx) { res += s[i]; mx = s[i]; }
    }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k; cin >> n >> k;
    string s; cin >> s;
    // Binary search on the answer string.
    // The answer is the lexicographically smallest string T such that
    // we can partition S into k parts where each f(part) <= T.
    //
    // For a given T: can we partition S into k parts where f(part) <= T?
    // f(part) <= T means: the largest subsequence of part is <= T lexicographically.
    // This means: for each character c in part that's >= T[0], we need to check...
    //
    // Actually, f(part) <= T iff the largest subsequence of part is <= T.
    // The largest subsequence is formed by taking all characters from right to left
    // that are >= the current max. So f(part) is determined by the suffix maximums.
    //
    // For f(part) <= T: the first character of f(part) must be <= T[0].
    // If f(part)[0] < T[0]: OK.
    // If f(part)[0] == T[0]: check f(part)[1] <= T[1], etc.
    //
    // This is complex. Let me use a different approach.
    // Binary search on the answer character by character.
    //
    // For the answer, try each character position.
    // At position 0: try 'a' to 'z'. For each candidate c:
    //   Check if we can partition S into k parts where each f(part) starts with <= c.
    //   If starts with c: further check the remaining characters.
    //
    // Greedy: to minimize max f(part), we want to split at points where f(part) is small.
    // The optimal split: each part's f(part) should be as small as possible.
    //
    // Simple approach: binary search on the answer string.
    // But strings are hard to binary search on.
    //
    // Alternative: greedy partition.
    // For each part, f(part) = largest subsequence = sequence of suffix maximums.
    // To minimize max f(part): we want to avoid parts with large characters early.
    //
    // Greedy: scan S left to right. At each position, decide whether to cut.
    // Cut when the current part's f(part) would exceed the answer.
    //
    // Let me just use a greedy: find the answer character by character.
    
    // The answer is the smallest string T such that we can partition into k parts
    // where each f(part) <= T.
    //
    // For a given string T, check if partition is possible:
    // Greedy: for each part, take the longest prefix where f(prefix) <= T.
    // If we can make k parts: T is achievable.
    
    // Binary search on answer length and characters.
    // First, find the first character of the answer.
    // The answer's first character = min over all valid partitions of max over parts of f(part)[0].
    // f(part)[0] = max character in part (from the right).
    // Actually, f(part) starts with the largest character in part (from the rightmost occurrence).
    // Wait, f(part) = largest subsequence = suffix maximum sequence.
    // f(part)[0] = the rightmost character that's >= all characters to its right.
    // Actually, f(part) is formed by scanning right to left and taking characters >= current max.
    // f(part)[0] = the first character taken from the left = the leftmost suffix maximum.
    // f(part)[0] = the maximum character in the part (from the leftmost occurrence of the max).
    //
    // Hmm, let me think again. f("sky aqua"):
    // Scan right to left: a (max=a), q>=a (max=q), u>=q (max=u), a<u, space, y>=u (max=y), k<y, s<y.
    // f = reverse of [a,q,u,y] = y, u, q, a. Wait, that's "yuqa".
    // But the sample says f("sky") = "y" and f("aqua") = "ua".
    // f("sky"): scan right to left: y (max=y), k<y, s<y. f = "y". Correct.
    // f("aqua"): scan right to left: a (max=a), u>=a (max=u), q<u, a<u. f = reverse of [a,u] = "ua". Correct.
    
    // So f(part)[0] = the maximum character in the part.
    // To minimize max f(part)[0]: we want each part's max character to be small.
    // The answer's first character = the smallest c such that we can partition into k parts
    // where each part's max character <= c.
    // This is: the k-th smallest "segment maximum" when we partition to minimize the k-th largest max.
    //
    // Greedy: sort all possible segment maximums and find the k-th.
    // Actually, the minimum possible max over k parts is:
    // For a given c: can we partition into k parts where each part's max <= c?
    // Each part can only contain characters <= c.
    // So we need to split at every character > c.
    // Number of parts = number of segments of consecutive characters <= c.
    // If this >= k: c is achievable.
    // Binary search on c: find the smallest c where segments >= k.
    
    // But the answer is a string, not just a character. After the first character,
    // we need to find the second character, etc.
    
    // Let me implement this properly.
    string ans = "";
    string remaining = s;
    int parts_left = k;
    
    for (int iter = 0; iter < 100 && parts_left > 0; iter++) {
        // Find the smallest character c such that we can partition remaining into
        // parts_left parts where each f(part) starts with <= c.
        // f(part) starts with the max character in the part.
        // So we need each part's max <= c.
        // Split at characters > c. Count segments.
        // If segments >= parts_left: c is achievable.
        
        char best_c = 'z';
        for (char c = 'a'; c <= 'z'; c++) {
            int segments = 0;
            bool in_seg = false;
            for (char ch : remaining) {
                if (ch <= c) {
                    if (!in_seg) { segments++; in_seg = true; }
                } else {
                    in_seg = false;
                }
            }
            if (segments >= parts_left) { best_c = c; break; }
        }
        ans += best_c;
        // Remove one part: take the first segment whose max == best_c
        // and whose f(part) is as small as possible.
        // Actually, we just need to remove any segment with max == best_c.
        // The greedy: take the longest prefix where max <= best_c.
        int cut = 0;
        bool found = false;
        for (int i = 0; i < (int)remaining.size(); i++) {
            if (remaining[i] > best_c) {
                if (!found) { cut = i; found = true; }
                break;
            }
            if (i == (int)remaining.size() - 1) {
                cut = remaining.size();
                found = true;
            }
        }
        if (!found) cut = remaining.size();
        // But we also need to handle the case where the segment's f(part) > ans.
        // For now, just cut at the first position where we can.
        // More precisely: cut at the first position where the segment's max == best_c
        // and the segment is valid.
        
        // Actually, let me just cut the first segment.
        int seg_end = 0;
        for (int i = 0; i < (int)remaining.size(); i++) {
            if (remaining[i] > best_c) { seg_end = i; break; }
            if (i == (int)remaining.size() - 1) seg_end = remaining.size();
        }
        remaining = remaining.substr(seg_end);
        parts_left--;
    }
    
    cout << ans << "\n";
    return 0;
}
