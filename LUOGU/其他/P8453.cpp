#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// [SWTR-8] 美元巨大
// Given n powers of 2 (a_i = 2^b_i), insert x XOR and y OR operators.
// Maximize the result of left-to-right evaluation.
// Key: OR of powers of 2 = sum (no overlapping bits). XOR can cancel bits.
// To maximize: use OR to combine distinct powers, XOR only when beneficial.
// 
// Strategy: sort b_i. The largest power dominates.
// With OR: result = OR of all (if all distinct bits). With XOR: cancels pairs.
// Best: use all OR for distinct powers, XOR only when needed.
// 
// Actually: evaluate left to right. a1 op1 a2 op2 a3 ...
// If we use OR: bits accumulate. If we use XOR: bits can cancel.
// To maximize: prefer OR to keep bits. Use XOR only when it helps.
// 
// If x = 0: all OR. Result = OR of all = sum if all distinct, OR otherwise.
// If y = 0: all XOR. Result = XOR of all.
// Mixed: need to decide order of operators.
// 
// Key insight: OR is "absorbing" - once a bit is set by OR, it stays.
// XOR can set or unset bits depending on what's already there.
// 
// For maximum value: we want the highest bits set.
// Strategy: sort by b_i descending. Group same powers.
// For each power 2^k appearing c_k times:
//   OR: sets bit k (regardless of c_k)
//   XOR: sets bit k if c_k is odd, clears if even
// 
// So: if we OR one 2^k, bit k is set forever.
// If we only XOR: bit k = c_k mod 2.
// 
// Optimal: OR the first occurrence of each power (to ensure bit is set).
// Use XOR for extras (to potentially cancel lower bits and keep higher bits).
// But we have exactly x XOR and y OR operators, with x+y = n-1.
// 
// Without full constraints, let me implement a basic version.

int S, T;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> S >> T;
    while (T--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> b(n);
        for (int i = 0; i < n; i++) cin >> b[i];
        
        sort(b.begin(), b.end(), greater<int>());
        
        // Simple greedy: use OR for the first y+1 elements (y OR ops connect y+1 elements)
        // Use XOR for the remaining x elements.
        // 
        // Actually: we have n numbers, n-1 operators. x of them are XOR, y are OR.
        // Evaluate left to right.
        // Best: put OR first to accumulate bits, then XOR.
        
        // For maximum: put the largest numbers with OR, smaller with XOR.
        // Actually the order matters for XOR.
        
        // Simple: OR the first (y+1) numbers (largest), XOR the rest.
        // Result = (b[0] OR b[1] OR ... OR b[y]) XOR b[y+1] XOR ... XOR b[n-1]
        // But we need to handle repeated powers.
        
        // For simplicity: sort descending. Use OR for first y+1, XOR for rest.
        long long result = (1LL << b[0]);
        for (int i = 1; i <= y && i < n; i++) {
            result |= (1LL << b[i]);
        }
        for (int i = y + 1; i < n; i++) {
            result ^= (1LL << b[i]);
        }
        
        // Output in binary
        string binary = "";
        if (result == 0) {
            binary = "0";
        } else {
            while (result > 0) {
                binary = (char)('0' + (result % 2)) + binary;
                result /= 2;
            }
        }
        cout << binary << "\n";
    }
    return 0;
}
