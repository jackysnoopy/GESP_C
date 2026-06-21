#include <iostream>
#include <vector>
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
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        
        // Compute b without move: keep a[i] if a[i] >= max(a[i+1..n-1])
        vector<int> suf(n);
        suf[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) suf[i] = max(a[i], suf[i + 1]);
        
        vector<int> b_no_move;
        for (int i = 0; i < n; i++) {
            if (i == n - 1 || a[i] >= suf[i + 1]) b_no_move.push_back(a[i]);
        }
        
        // With move: we move one element from position j to position i (i < j).
        // Best strategy: move the element that gives lexicographically largest b.
        // 
        // Key observation: b without move is non-increasing.
        // The first element of b is a[0] if a[0] == suf[0] (global max), otherwise we skip a[0].
        // 
        // If we move a[j] (the global max or some large element) to position 0:
        //   b starts with max of {moved element, remaining}.
        //   The moved element at position 0 will always be kept (it's the first and likely max).
        //   Then the rest follows the greedy.
        //
        // For the lexicographically largest b:
        // 1. First, we want b[0] to be as large as possible.
        //    The max possible b[0] = global max of a.
        //    If a[0] is already the global max, b[0] = global max without move.
        //    Otherwise, we can bring the global max to position 0 with one move.
        //
        // 2. After fixing b[0], we want b[1] to be as large as possible.
        //    The remaining elements (after removing the moved one from its original position)
        //    determine the rest of b.
        
        // Strategy: find the optimal move.
        // Move element a[j] to position 0 for each candidate j, and compute the resulting b.
        // But we can't try all j in O(n) each.
        
        // Key insight: after moving a[j] to position 0, the array becomes:
        // [a[j], a[0], a[1], ..., a[j-1], a[j+1], ..., a[n-1]]
        // b is computed greedily on this array.
        
        // The b starts with a[j] (it's the first element, and a[j] is >= a[0] if a[j] is the max).
        // Actually a[j] might not be >= all remaining. But since we choose j to maximize b,
        // we should choose j where a[j] is large.
        
        // Better approach:
        // Without move, b is a subsequence where each element >= all elements after it.
        // With move, we can improve b by bringing a large element earlier.
        
        // The optimal move:
        // Consider the first position in b_no_move where we could improve.
        // b_no_move[0] = a[i0] where i0 is the first position with a[i0] >= suf[i+1].
        // If a[i0] == suf[0] (global max), no improvement possible for b[0].
        // Otherwise, we can bring suf[0] to position 0, making b[0] = suf[0].
        
        // After bringing suf[0] (at some position j0) to position 0:
        // New array: [suf[0], a[0], ..., a[j0-1], a[j0+1], ..., a[n-1]]
        // b[0] = suf[0] (always kept as first).
        // Then b[1..] is the greedy on [a[0], ..., a[j0-1], a[j0+1], ..., a[n-1]].
        // But we need to be careful: some elements before position j0 might be larger than
        // the remaining suffix after removing a[j0].
        
        // This is still complex. Let me use a different approach.
        // For each possible first element of b, compute the best b starting with that element.
        
        // Actually, the key insight for the O(n) solution:
        // The answer b is always a non-increasing sequence.
        // Without move: b is the "suffix maximum" subsequence.
        // With move: we can improve by one position.
        
        // Let me think about what move gives the best improvement.
        // The b without move is: b[0], b[1], ..., b[k-1] where b[i] = a[pos[i]] and
        // b[0] >= b[1] >= ... >= b[k-1].
        
        // If b[0] is not the global max, we can bring the global max to position 0.
        // The resulting b starts with global max.
        
        // After the global max is at position 0, the rest of b is determined by:
        // Take the original array, remove the global max from its original position,
        // and prepend it.
        
        // Let's say global max is at position j0 with value M.
        // New array: [M, a[0], a[1], ..., a[j0-1], a[j0+1], ..., a[n-1]]
        // b = [M] + greedy([a[0], ..., a[j0-1], a[j0+1], ..., a[n-1]])
        
        // But we also need to consider: what if the first element of b_no_move is already M?
        // Then moving M to position 0 doesn't help (b[0] is already M).
        // In that case, we should try to improve b[1].
        
        // General approach: 
        // 1. Compute b_no_move.
        // 2. For each element M that we could bring to improve b, compute the resulting b.
        // 3. Take the lexicographically largest.
        
        // Since b is non-increasing and we want to maximize it:
        // The improvement is: at the first position where b_new > b_old, take the larger one.
        
        // For O(n) solution:
        // Compute b_no_move. Find first position where it's not optimal.
        // Try moving the best element to improve that position.
        
        // Actually, the simplest correct O(n) approach:
        // 1. Find the global max M and its position j0.
        // 2. If b_no_move[0] == M, try to improve b[1].
        //    To improve b[1], find the max among remaining elements after removing one.
        // 3. If b_no_move[0] < M, moving M to position 0 gives b[0] = M > b_no_move[0].
        //    Compute the rest of b.
        
        // Let me compute both candidates and take the max:
        // Candidate 1: b_no_move (no move)
        // Candidate 2: move global max to position 0
        
        int globalMax = suf[0];
        vector<int> best = b_no_move;
        
        // Find all positions of global max
        vector<int> maxPos;
        for (int i = 0; i < n; i++) if (a[i] == globalMax) maxPos.push_back(i);
        
        // Try moving first occurrence of global max to position 0
        if (maxPos[0] != 0) {
            int j0 = maxPos[0];
            vector<int> modified;
            modified.push_back(a[j0]);
            for (int i = 0; i < n; i++) if (i != j0) modified.push_back(a[i]);
            // Compute b for modified
            vector<int> suf2(modified.size());
            int m = modified.size();
            suf2[m - 1] = modified[m - 1];
            for (int i = m - 2; i >= 0; i--) suf2[i] = max(modified[i], suf2[i + 1]);
            vector<int> b2;
            for (int i = 0; i < m; i++) {
                if (i == m - 1 || modified[i] >= suf2[i + 1]) b2.push_back(modified[i]);
            }
            if (b2 > best) best = b2;
        }
        
        // Also consider: what if b[0] is already M?
        // Then we should try to improve b[1] by moving a suitable element.
        // Find the first position where b_no_move could be improved.
        if (b_no_move[0] == globalMax && b_no_move.size() > 1) {
            // b_no_move[1] should be improved.
            // Find position in a where b_no_move[1] is chosen (first element < b_no_move[0] that >= suffix)
            // Actually, b_no_move[1] is the second element of the suffix-max subsequence.
            // To improve it, we need a larger element between the position of b_no_move[0] and b_no_move[1]
            // that was skipped.
            
            // Find positions in a corresponding to b_no_move elements
            vector<int> bpos;
            int bp = 0;
            for (int i = 0; i < n && bp < (int)b_no_move.size(); i++) {
                if (a[i] == b_no_move[bp]) { bpos.push_back(i); bp++; }
            }
            
            // Between bpos[0] and bpos[1], find the max element that was skipped
            if (bpos.size() >= 2) {
                int maxSkipped = 0;
                int maxSkipPos = -1;
                for (int i = bpos[0] + 1; i < bpos[1]; i++) {
                    if (a[i] > maxSkipped) { maxSkipped = a[i]; maxSkipPos = i; }
                }
                if (maxSkipped > b_no_move[1] && maxSkipPos >= 0) {
                    // Move a[maxSkipPos] to just before bpos[1] (or to position bpos[0]+1)
                    // Actually, move it to position bpos[0] + 1 (right after the first b element)
                    // But we need to move it to an earlier position. Let's move it to position bpos[0]+1.
                    // Actually: move it to any position before its current position.
                    // The effect on b: the element appears earlier, potentially becoming b[1].
                    
                    // Move maxSkipPos to position bpos[0] + 1
                    vector<int> modified2;
                    for (int i = 0; i < n; i++) {
                        if (i == maxSkipPos) continue;
                        modified2.push_back(a[i]);
                        if (i == bpos[0]) modified2.push_back(a[maxSkipPos]); // insert after first b element
                    }
                    // Hmm, this insertion logic is tricky. Let me just move to position 0 of the subarray.
                    // Actually move to position bpos[0]+1 in the original array.
                    vector<int> mod2;
                    for (int i = 0; i < n; i++) {
                        if (i == bpos[0] + 1 && mod2.size() > 0) {
                            mod2.push_back(a[maxSkipPos]);
                        }
                        if (i != maxSkipPos) mod2.push_back(a[i]);
                    }
                    if ((int)mod2.size() < n) mod2.push_back(a[maxSkipPos]); // shouldn't happen
                    
                    int m2 = mod2.size();
                    vector<int> suf3(m2);
                    suf3[m2 - 1] = mod2[m2 - 1];
                    for (int i = m2 - 2; i >= 0; i--) suf3[i] = max(mod2[i], suf3[i + 1]);
                    vector<int> b3;
                    for (int i = 0; i < m2; i++) {
                        if (i == m2 - 1 || mod2[i] >= suf3[i + 1]) b3.push_back(mod2[i]);
                    }
                    if (b3 > best) best = b3;
                }
            }
        }
        
        for (int i = 0; i < (int)best.size(); i++) {
            if (i) cout << " ";
            cout << best[i];
        }
        cout << "\n";
    }
    return 0;
}
