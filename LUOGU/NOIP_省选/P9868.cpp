#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    // For each word i, can we permute it (and all others) so that w[i] is lex smallest?
    // Each word can have its characters rearranged arbitrarily.
    // After rearrangement, w'[i] must be lex smallest among all w'.
    // w'[i] is the sorted version of w[i] (lex smallest permutation).
    // For w'[i] to be smallest, it must be < sorted(w[j]) for all j!=i.
    // But we can also rearrange w[j] to be NOT sorted (lex larger).
    // Actually: w'[j] can be any permutation of w[j].
    // For w'[i] < w'[j], we need at least one position where w'[i][k] < w'[j][k].
    // Since we control both permutations, w'[i] should be sorted ascending (lex smallest).
    // And w'[j] should be sorted descending or whatever makes w'[i] < w'[j].
    // 
    // Key: w'[i] = sorted(w[i]) ascending. 
    // w'[j] = we want it to be as large as possible to ensure w'[i] < w'[j].
    // w'[j] max = sorted(w[j]) descending.
    // But actually: we just need w'[i] < w'[j] for SOME permutation w'[j].
    // The condition w'[i] < w'[j] holds iff sorted(w[i]) < sorted(w[j]) ascending? No.
    // 
    // Actually: the question is whether there EXISTS permutations such that w'[i] is smallest.
    // w'[i] must be < w'[j] for all j. 
    // w'[i] = sorted(w[i]) ascending (best for i).
    // w'[j] = any permutation of w[j].
    // We want: sorted(w[i]) < any_possible(w'[j]) for all j!=i.
    // Actually we want sorted(w[i]) < w'[j] for ALL j!=i.
    // Since w'[j] can be any permutation, the LARGEST w'[j] is sorted(w[j]) descending.
    // If sorted_asc(w[i]) < sorted_desc(w[j]), then w'[i] < w'[j] is achievable.
    // But sorted_asc(w[i]) < sorted_desc(w[j]) just means at least one position k where
    // sorted_asc(w[i])[k] < sorted_desc(w[j])[k].
    // 
    // Actually: if sorted_asc(w[i]) < sorted_asc(w[j]) in lex order, then we can always
    // make w'[i] < w'[j] (by making w'[j] = sorted_asc(w[j])).
    // If sorted_asc(w[i]) >= sorted_asc(w[j]), can we still make w'[i] < w'[j]?
    // We can make w'[j] = sorted_desc(w[j]). If sorted_asc(w[i]) < sorted_desc(w[j]), yes.
    // 
    // For w'[i] to be lex smallest overall, for EACH j!=i:
    // There must exist some permutation of w[j] that is > sorted_asc(w[i]).
    // The maximum permutation of w[j] is sorted_desc(w[j]).
    // So condition: sorted_asc(w[i]) < sorted_desc(w[j]) for all j!=i.
    // 
    // If sorted_asc(w[i]) == sorted_desc(w[j]) for some j, they have the same multiset.
    // Then any permutation of w[j] == some permutation of w[i].
    // Can w'[i] < w'[j]? If they have the same characters, any permutations can be
    // equal or different. For lex less, we need some position where w'[i] < w'[j].
    // If w[i] and w[j] are the same multiset, the sorted ascending of both is the same.
    // So sorted_asc(w[i]) is NOT < sorted_asc(w[j]) (they're equal).
    // And sorted_asc(w[i]) < sorted_desc(w[j]) iff sorted_asc != sorted_desc
    // (which is true if there are at least 2 different characters).
    // 
    // So for each word i, check: for all j!=i, sorted_asc(w[i]) < sorted_desc(w[j]).
    // But n*m up to 3000*3000 = 9M, and for each pair we compare strings of length m.
    // That's O(n^2 * m) = 27 billion. Too slow.
    // 
    // Better: sort all words by sorted_asc. Then for word i at rank r:
    // - All words before i have sorted_asc <= sorted_asc(w[i])
    // - We need sorted_desc of all of them to be > sorted_asc(w[i])
    // 
    // Actually: if sorted_asc(w[i]) < sorted_asc(w[j]) for all j before i (in sorted order),
    // then condition holds for those j.
    // For j after i: sorted_asc(w[j]) >= sorted_asc(w[i]).
    // We need sorted_desc(w[j]) > sorted_asc(w[i]). Since sorted_desc(w[j])[0] >= sorted_asc(w[j])[0]
    // >= sorted_asc(w[i])[0], this is usually true unless all chars are the same.
    // 
    // Simpler approach: O(n^2*m) might be OK for n,m <= 3000... 
    // 3000^2 * 3000 = 27 billion. No, too slow.
    // 
    // O(n*m + n^2): precompute sorted_asc and sorted_desc for each word.
    // Then for each pair, compare strings O(m). Still O(n^2*m).
    // 
    // Optimized: for each word i, find the minimum sorted_desc among all j!=i.
    // If sorted_asc(w[i]) < min_sorted_desc_excluding_i, then i is valid.
    // But min_sorted_desc changes per i (exclude different j each time).
    // 
    // Precompute: min1 = min sorted_desc, min2 = second min.
    // If w[i]'s sorted_desc != min1, then min excluding i = min1.
    // Else min excluding i = min2.
    // Then check sorted_asc(w[i]) < min_excluding_i.
    // But we're comparing sorted_asc with sorted_desc, which may have different lengths
    // (actually same length m). And lexicographic comparison.
    // 
    // This works! O(n*m) for sorting, O(n*m) for comparisons.
    
    vector<string> sortedAsc(n), sortedDesc(n);
    for (int i = 0; i < n; i++) {
        sortedAsc[i] = w[i];
        sort(sortedAsc[i].begin(), sortedAsc[i].end());
        sortedDesc[i] = sortedAsc[i];
        reverse(sortedDesc[i].begin(), sortedDesc[i].end());
    }
    
    // Find min and second min of sortedDesc
    int min1 = 0, min2 = -1;
    for (int i = 1; i < n; i++) {
        if (sortedDesc[i] < sortedDesc[min1]) {
            min2 = min1;
            min1 = i;
        } else if (min2 == -1 || sortedDesc[i] < sortedDesc[min2]) {
            min2 = i;
        }
    }
    
    string result(n, '0');
    for (int i = 0; i < n; i++) {
        string& minDesc = (i == min1 && min2 != -1) ? sortedDesc[min2] : sortedDesc[min1];
        if (sortedAsc[i] < minDesc) {
            result[i] = '1';
        }
    }
    
    cout << result << "\n";
    return 0;
}
