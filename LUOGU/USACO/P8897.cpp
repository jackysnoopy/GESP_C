#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<string> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];
    // For each position, count which letters appear in each word
    // A word can be assigned to position j if all its letters are in the allowed set
    // Use bipartite matching: words to positions
    // For small constraints, try greedy/hungarian
    // Actually just try all permutations of positions for words
    // With n<=15, m<=15, we can use bitmask DP
    vector<vector<int>> cnt(n, vector<int>(26, 0));
    for (int i = 0; i < n; i++) {
        for (char c : w[i]) cnt[i][c-'a']++;
    }
    vector<int> ans(n, 0);
    // Simple greedy: for each word, find first position where all its letters fit
    // Actually this is assignment problem. Use Hungarian or DP.
    // For n,m up to 15: bitmask DP
    // dp[mask] = true if words in mask can be assigned to positions 0..popcount(mask)-1
    int full = (1 << n) - 1;
    vector<bool> dp(full + 1, false);
    vector<int> from(full + 1, -1);
    dp[0] = true;
    for (int mask = 0; mask <= full; mask++) {
        if (!dp[mask]) continue;
        int pos = __builtin_popcount(mask);
        if (pos >= m) continue;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            // Check if word i can go to position pos
            bool ok = true;
            for (int c = 0; c < 26; c++) {
                if (cnt[i][c] > 1) { ok = false; break; }
            }
            if (ok) {
                int nmask = mask | (1 << i);
                if (!dp[nmask]) {
                    dp[nmask] = true;
                    from[nmask] = i;
                }
            }
        }
    }
    // Find best mask
    int best = 0;
    for (int mask = 0; mask <= full; mask++) {
        if (dp[mask] && __builtin_popcount(mask) > __builtin_popcount(best)) {
            best = mask;
        }
    }
    // Reconstruct assignment
    vector<int> assignment(n, -1);
    int mask = best;
    int pos = __builtin_popcount(mask) - 1;
    while (mask > 0) {
        int word = from[mask];
        assignment[word] = pos;
        pos--;
        mask ^= (1 << word);
    }
    for (int i = 0; i < n; i++) {
        cout << (assignment[i] == -1 ? 0 : assignment[i] + 1);
    }
    cout << "\n";
    return 0;
}
