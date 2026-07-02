#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int P;
    cin >> P;
    int T;
    cin >> T;
    if (P == 1) {
        while (T--) {
            string s;
            cin >> s;
            int n = s.size();
            // Check if RGB readable
            // RGB readable: can color each char R, G, B such that:
            // Removing all B gives valid bracket sequence
            // Removing all R gives valid bracket sequence
            //
            // Greedy: process left to right
            // Track balance for the "B-removed" sequence and "R-removed" sequence
            // balance_B = (#( in B-removed) - (#) in B-removed)
            // balance_R = (#( in R-removed) - (#) in R-removed)
            //
            // For '(': both balances increase
            // For ')': we need to choose R or B to remove, or keep
            //   If we remove it from B-sequence: balance_B unchanged, balance_R decreases
            //   If we remove it from R-sequence: balance_B decreases, balance_R unchanged
            //   If we keep it: both decrease
            //
            // We want both balances >= 0 at all times
            //
            // Strategy: for ')', try to keep it if both balances > 0
            // Otherwise, remove from the one with higher balance

            string color(n, ' ');
            int balB = 0, balR = 0;
            bool ok = true;
            for (int i = 0; i < n; i++) {
                if (s[i] == '(') {
                    balB++;
                    balR++;
                    color[i] = 'G'; // Green (kept in both)
                } else {
                    // s[i] == ')'
                    if (balB > 0 && balR > 0) {
                        // Can keep in both
                        balB--;
                        balR--;
                        color[i] = 'G';
                    } else if (balB > 0) {
                        // Must remove from R
                        balB--;
                        color[i] = 'B';
                    } else if (balR > 0) {
                        // Must remove from B
                        balR--;
                        color[i] = 'R';
                    } else {
                        ok = false;
                        break;
                    }
                }
            }
            if (balB != 0 || balR != 0) ok = false;
            if (!ok) {
                cout << "impossible\n";
            } else {
                cout << color << "\n";
            }
        }
    } else {
        // P = 2: count RGB readable bracket sequences of length N
        // A bracket sequence of length N (N must be even)
        // RGB readable means: removing all R gives valid, removing all B gives valid
        //
        // Equivalently: each '(' can be R, G, or B; each ')' can be R, G, or B
        // After removing R: valid bracket sequence
        // After removing B: valid bracket sequence
        //
        // Let's think of it as: we have a bracket sequence of length N.
        // For each position, if it's '(', it contributes to both sequences.
        // If it's ')', we choose to put it in R-set, B-set, or both (G).
        //
        // Actually the coloring is: each char is R, G, or B.
        // Removing R chars: the remaining (G+B) must form valid bracket seq.
        // Removing B chars: the remaining (G+R) must form valid bracket seq.
        //
        // For '(' at position i: if colored R, it's in R-set but not B-set.
        //   B-removed has it, R-removed doesn't.
        //   B-sequence: (+1), R-sequence: (+0)
        // If colored B: B-sequence: (+0), R-sequence: (+1)
        // If colored G: B-sequence: (+1), R-sequence: (+1)
        //
        // For ')' at position i: similar but -1.
        //
        // So for '(': choices are R(+1B,0R), B(0B,+1R), G(+1B,+1R)
        // For ')': choices are R(-1B,0R), B(0B,-1R), G(-1B,-1R)
        //
        // We need both B-balance and R-balance to stay >= 0 and end at 0.
        //
        // DP: dp[i][b][r] = number of ways for first i chars with B-balance=b, R-balance=r
        // N up to 300, so b,r up to 150. dp[300][151][151] is feasible.
        
        while (T--) {
            int N;
            cin >> N;
            if (N % 2 != 0) {
                cout << 0 << "\n";
                continue;
            }
            int half = N / 2;
            // dp[b][r] = number of ways
            vector<vector<long long>> dp(half + 1, vector<long long>(half + 1, 0));
            dp[0][0] = 1;
            for (int i = 0; i < N; i++) {
                vector<vector<long long>> ndp(half + 1, vector<long long>(half + 1, 0));
                for (int b = 0; b <= half; b++) {
                    for (int r = 0; r <= half; r++) {
                        if (dp[b][r] == 0) continue;
                        if (i < N / 2) {
                            // '('
                            // R: b+1, r
                            if (b + 1 <= half) ndp[b + 1][r] = (ndp[b + 1][r] + dp[b][r]) % MOD;
                            // B: b, r+1
                            if (r + 1 <= half) ndp[b][r + 1] = (ndp[b][r + 1] + dp[b][r]) % MOD;
                            // G: b+1, r+1
                            if (b + 1 <= half && r + 1 <= half)
                                ndp[b + 1][r + 1] = (ndp[b + 1][r + 1] + dp[b][r]) % MOD;
                        } else {
                            // ')'
                            // R: b-1, r (if b > 0)
                            if (b > 0) ndp[b - 1][r] = (ndp[b - 1][r] + dp[b][r]) % MOD;
                            // B: b, r-1 (if r > 0)
                            if (r > 0) ndp[b][r - 1] = (ndp[b][r - 1] + dp[b][r]) % MOD;
                            // G: b-1, r-1 (if b > 0 && r > 0)
                            if (b > 0 && r > 0)
                                ndp[b - 1][r - 1] = (ndp[b - 1][r - 1] + dp[b][r]) % MOD;
                        }
                    }
                }
                dp = ndp;
            }
            cout << dp[0][0] << "\n";
        }
    }
    return 0;
}
