#include <iostream>
#include <vector>
using namespace std;

// P1338: 逆序对
// Find the permutation of 1..n with exactly m inversions.
// Greedy: place largest numbers first to maximize inversions.
// Each number k placed at position p creates p inversions (with all larger numbers after it).
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long m;
    cin >> n >> m;
    
    vector<int> ans(n);
    int lo = 0, hi = n - 1;
    for (int i = n; i >= 1; i--) {
        // We have (hi - lo + 1) positions. 
        // If we place i at position lo + k (0-indexed), it creates k inversions
        // (with larger numbers placed before it... wait, larger numbers are placed first).
        // Actually: we place numbers from n down to 1.
        // When placing number i, all numbers > i are already placed.
        // If we place i at position p (among remaining slots), it creates 
        // (number of slots before p that are empty) inversions... 
        // Hmm, let me think differently.
        //
        // Alternative: build from right to left.
        // Place 1 at position n. Then 2, etc.
        // Number i placed at position j creates (n-j) inversions with numbers > i that will be placed after.
        // But those aren't placed yet.
        //
        // Standard approach: place from left to right.
        // At each step, decide how many larger numbers go after this position.
        // 
        // Or: the permutation with exactly m inversions:
        // Use a greedy: for position 1, decide the value.
        // If value = k, it creates (k-1) inversions (with numbers > k that come later).
        // But later numbers haven't been determined.
        //
        // Simpler: use the fact that the number of inversions of a permutation
        // where element at position i is a_i = sum of (a_i - 1 - count of smaller before).
        //
        // Standard construction: 
        // Start with [1,2,...,n] (0 inversions).
        // Each swap of adjacent elements increases inversions by 1.
        // To get m inversions: make m adjacent swaps.
        // But this gives a specific permutation, not necessarily the one the problem wants.
        //
        // The problem likely asks for a specific permutation. Without data file,
        // let me implement: find permutation of 1..n with exactly m inversions.
        
        // Place numbers from n to 1. Number k at position p creates p inversions
        // (it's smaller than all previously placed numbers, and p of them are after it).
        
        // Actually: if we place n first, it creates 0 inversions (nothing after it is smaller).
        // Place n-1: if placed at the end, 0 inversions. If placed before n, 1 inversion.
        // Place k: if placed at position p (0-indexed from left among remaining slots),
        // it creates p inversions (p previously placed numbers are after it, all larger).
        
        // So: we need to place numbers from n down to 1.
        // Number k (from n to 1) creates p_k inversions where 0 <= p_k <= (n-k).
        // Sum of p_k = m.
        // 
        // To find the permutation: for each k from n to 1:
        //   p_k = min(m, n - k) ... no, we need sum = m.
        //   Greedy: p_k = min(m, n - k) for k = n, n-1, ...
        //   But we need to track remaining positions.
        //
        // Let me use a BIT or direct construction.
        // 
        // Simpler: use the inverse approach.
        // Start with empty array of size n.
        // For k = n down to 1:
        //   Place k at position min(m, n-k) among remaining positions (from left, 0-indexed).
        //   Subtract min(m, n-k) from m.
        //
        // Wait, if k is placed at position p (0-indexed among remaining), 
        // it creates p inversions with all larger numbers already placed.
        // We want p = min(m, remaining_slots - 1).
        
        int remaining = hi - lo + 1;
        int pos = min((long long)remaining - 1, m);
        ans[lo + pos] = i;
        m -= pos;
        // Remove position lo+pos from consideration
        // Shift: mark this position as used
        // Actually let me use a different approach with a set of available positions
        break; // restructure
    }
    
    // Rewrite using a set of positions
    vector<int> result(n, 0);
    vector<int> avail;
    for (int i = 0; i < n; i++) avail.push_back(i);
    
    for (int k = n; k >= 1; k--) {
        int remaining = (int)avail.size();
        int pos = (int)min((long long)remaining - 1, m);
        result[avail[pos]] = k;
        m -= pos;
        avail.erase(avail.begin() + pos);
    }
    
    for (int i = 0; i < n; i++) {
        cout << result[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
