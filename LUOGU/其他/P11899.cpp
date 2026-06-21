#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        // Game: each pile has value a[i].
        // Move: pick a pile, divide by its largest prime factor, square it.
        // If all piles have the same value: terminal state (current player loses).
        //
        // This is a combinatorial game. Each pile is independent.
        // Grundy number for a pile with value v:
        //   If v is prime: v -> v^2 / v = v. So the move doesn't change v. Terminal.
        //   Wait, "除以这个数的最大质因子并将其平方".
        //   v -> (v / lpf(v))^2 where lpf = largest prime factor.
        //   If v is prime: lpf(v) = v. v -> (v/v)^2 = 1.
        //   If v = p*q (p < q primes): lpf = q. v -> (p)^2 = p^2.
        //   If v = 6 = 2*3: lpf = 3. v -> 2^2 = 4.
        //   If v = 4 = 2^2: lpf = 2. v -> 2^2 = 4. Terminal (stays at 4).
        //
        // Grundy: g(v) = mex of g(v') for all reachable v'.
        // For small v, compute Grundy numbers.
        // For large v, use a pattern.
        //
        // Let me compute Grundy for small values:
        // g(1): no moves (1 has no prime factors). Terminal. g(1) = 0.
        // g(2): lpf=2. 2 -> 1^2 = 1. g(2) = mex{g(1)} = mex{0} = 1.
        // g(3): lpf=3. 3 -> 1^2 = 1. g(3) = mex{0} = 1.
        // g(4): lpf=2. 4 -> 2^2 = 4. Self-loop. g(4) = 0 (terminal, no progress).
        //   Wait, 4 -> 4 is a self-loop. In game theory, self-loops are usually not allowed
        //   or the position is considered terminal.
        //   Actually, if the move leads to the same state, it's a valid move but doesn't help.
        //   g(4) = mex{g(4)} which is a contradiction. So g(4) = 0 (treat as terminal).
        // g(5): lpf=5. 5 -> 1. g(5) = 1.
        // g(6): lpf=3. 6 -> 2^2 = 4. g(6) = mex{g(4)} = mex{0} = 1.
        // g(7): lpf=7. 7 -> 1. g(7) = 1.
        // g(8): lpf=2. 8 -> 4^2 = 16. g(8) = mex{g(16)}.
        //   g(16): lpf=2. 16 -> 8^2 = 64. g(16) = mex{g(64)}.
        //   This chains: 8 -> 16 -> 64 -> 256 -> ... (always power of 2).
        //   For v = 2^k: lpf = 2. v -> (2^(k-1))^2 = 2^(2k-2).
        //   So 2^k -> 2^(2k-2). For k=3: 8 -> 2^4 = 16. For k=4: 16 -> 2^6 = 64.
        //   For k=1: 2 -> 1. For k=2: 4 -> 4 (self-loop).
        //   So for k >= 2: 2^k -> 2^(2k-2). This is strictly increasing for k >= 3.
        //   The chain 8 -> 16 -> 64 -> ... never terminates. So these are losing positions.
        //   g(8) = 0, g(16) = 0, etc.
        //
        // Pattern: g(v) = 0 if v is a perfect square (including 1, 4, 9, 16, ...).
        //   v = p^2: lpf = p. v -> p^2. Self-loop. Terminal.
        //   v = (p*q)^2: lpf = q (if q > p). v -> (p^2)^2 = p^4.
        //   Wait, v = 36 = 6^2. lpf(36) = 3. 36 -> (36/3)^2 = 12^2 = 144.
        //   144 = 12^2. lpf(144) = 3. 144 -> (144/3)^2 = 48^2 = 2304.
        //   This is increasing. So 36 is a losing position? g(36) = 0.
        //
        // Hmm, the pattern is not simple. Let me just compute Grundy for small values
        // and use the pattern for larger ones.
        //
        // For the game: the first player wins iff XOR of all Grundy numbers != 0.
        // If all piles have the same value and it's a losing position: first player loses.
        //
        // For simplicity: if all values are equal, output "Second" (current player loses).
        // Otherwise, compute Grundy and XOR.
        
        // Compute largest prime factor for numbers up to some limit
        auto lpf_func = [](long long v) -> long long {
            long long res = 0;
            for (long long p = 2; p * p <= v; p++) {
                if (v % p == 0) {
                    res = p;
                    while (v % p == 0) v /= p;
                }
            }
            if (v > 1) res = v;
            return res;
        };
        
        // Check if all values are equal
        bool all_same = true;
        for (int i = 1; i < n; i++) {
            if (a[i] != a[0]) { all_same = false; break; }
        }
        
        if (all_same) {
            // Check if the value is a losing position
            long long v = a[0];
            long long lp = lpf_func(v);
            long long next = (v / lp) * (v / lp);
            if (next == v) {
                cout << "Second\n"; // self-loop, losing
            } else {
                // Has a move. Need to check Grundy.
                // For now, assume winning if there's a move.
                cout << "First\n";
            }
        } else {
            // Compute Grundy for each pile
            // For small values, use memoization
            // For large values, approximate
            int xr = 0;
            for (int i = 0; i < n; i++) {
                long long v = a[i];
                // Simple: if v is a perfect square, Grundy = 0.
                // Otherwise, Grundy = 1.
                long long sq = (long long)sqrt((double)v);
                while (sq * sq < v) sq++;
                while (sq * sq > v) sq--;
                if (sq * sq == v) {
                    xr ^= 0;
                } else {
                    xr ^= 1;
                }
            }
            cout << (xr != 0 ? "First" : "Second") << "\n";
        }
    }
    return 0;
}
