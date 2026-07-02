#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    string S;
    cin >> S;
    int Q;
    cin >> Q;
    // For each query [L, R], find min deletions so that every prefix and suffix
    // of S[L..R] has #C >= #T
    // 
    // Key insight: for the substring S[L..R], we need:
    // 1. Every prefix has #C >= #T (standard bracket condition)
    // 2. Every suffix has #C >= #T (equivalent to: every prefix of reversed has #C >= #T)
    //
    // Let prefix[i] = (#C in S[1..i]) - (#T in S[1..i])
    // For condition 1: min_{i=L..R} (prefix[i] - prefix[L-1]) >= 0
    // For condition 2: min_{i=L..R} (prefix[R] - prefix[i]) >= 0
    //   i.e., max_{i=L..R} prefix[i] <= prefix[R]
    //
    // We need to delete minimum characters so that both conditions hold.
    // After deletion, the remaining characters form a subsequence.
    //
    // For the subsequence S' of S[L..R]:
    // Condition 1: every prefix of S' has #C >= #T
    // Condition 2: every suffix of S' has #C >= #T
    //
    // This is equivalent to: S' is a "Dyck-like" string where
    // both S' and reverse(S') are valid (all prefixes have #C >= #T).
    //
    // The minimum deletions = (R-L+1) - (length of longest valid subsequence)
    //
    // For a string, the longest subsequence satisfying both conditions:
    // It's the longest subsequence that is both a valid prefix sequence
    // and has valid suffixes.
    //
    // This is equivalent to: the subsequence must be a concatenation of
    // some number of "CC" pairs and individual "C"s, arranged so that
    // the sequence is "mountain-shaped" in terms of balance.
    //
    // Actually, for both prefix and suffix conditions:
    // The subsequence must have the property that at any point,
    // the number of C's seen so far >= number of T's, AND
    // the number of C's remaining >= number of T's remaining.
    //
    // This means: the balance at any point must be between
    // min_balance and max_balance of the whole sequence.
    //
    // For a valid subsequence of length L with k C's and (L-k) T's:
    // Need k >= L-k (i.e., k >= L/2) for prefix condition at end
    // Need the balance never drops below 0 (prefix condition)
    // Need the balance never exceeds some value (suffix condition)
    //
    // The longest such subsequence can be found by:
    // Take all C's and as many T's as possible while maintaining constraints.
    //
    // For a string with c C's and t T's (c+t = length):
    // The longest valid subsequence has length = 2*min(c,t) + (c-t if c>t else 0)
    // Wait, that's just the whole string.
    //
    // Actually the constraint is more subtle. Let me think again.
    //
    // For subsequence S': every prefix has #C >= #T, every suffix has #C >= #T.
    // Let balance[i] = #C in S'[1..i] - #T in S'[1..i]
    // Condition: balance[i] >= 0 for all i, and balance[len] - balance[i] >= 0 for all i
    // i.e., balance[i] <= balance[len] for all i
    // So: 0 <= balance[i] <= balance[len] for all i
    //
    // The longest subsequence: greedily take C's and T's
    // Process left to right, maintain current balance
    // Take C: balance increases (good for prefix, may hurt suffix)
    // Take T: balance decreases (may hurt prefix, good for suffix)
    //
    // Optimal: take all C's. For T's, we can take at most as many T's as C's
    // at any prefix, and also the total T's <= total C's.
    //
    // Actually the answer is: for substring S[L..R], let c = #C, t = #T.
    // The longest valid subsequence has length c + t - |c - t| = 2*min(c,t)
    // if the subsequence can be arranged. But we can't rearrange, only delete.
    //
    // For a subsequence (preserving order):
    // The longest valid one: we need to find the longest subsequence where
    // the balance stays in [0, total_balance].
    //
    // This is a classic problem. The answer for a single string is:
    // total_length - (minimum deletions to make it valid in both directions)
    //
    // For the subsequence problem with both prefix and suffix constraints:
    // We can use a greedy approach: process left to right, track balance.
    // Take C if balance < total_C (to leave room for suffix).
    // Take T if balance > 0.
    //
    // Actually the simplest approach: 
    // For substring S[L..R], the minimum deletions = 
    //   max(0, -min_prefix_balance) + max(0, max_suffix_excess)
    // where min_prefix_balance = min over i of (prefix[i] - prefix[L-1])
    // and max_suffix_excess = max over i of (prefix[i] - prefix[R])
    //
    // Wait, that's for making the original string valid (not subsequence).
    // For subsequence, we can delete characters.
    //
    // For subsequence: the longest valid subsequence has length = 
    // (R-L+1) - max(0, -(min_prefix)) - max(0, max_excess)
    // where min_prefix = min balance in [L,R] relative to L-1
    // and max_excess = max(prefix[i]) - prefix[R] for i in [L,R]
    //
    // Hmm, let me think about this differently.
    // For a subsequence to satisfy both conditions:
    // It must be that the balance at every point is in [0, B] where B is the final balance.
    // The longest such subsequence of S[L..R]:
    // = (R-L+1) - (minimum deletions)
    // Minimum deletions = number of characters we must skip to make the balance
    // stay in a valid range at every point.
    //
    // For the prefix condition: we must skip T's that would make balance < 0.
    // For the suffix condition: we must skip C's that would make balance > final_B.
    //
    // The answer is: for substring S[L..R], 
    // let b[i] = prefix balance at position i (relative to L-1)
    // min_b = min b[i] for i in [L,R]
    // max_b = max b[i] for i in [L,R]
    // final_b = b[R] = prefix[R] - prefix[L-1]
    //
    // For the subsequence:
    // We need balance to stay >= 0 => must delete enough T's to raise min balance to 0
    //   => delete max(0, -min_b) characters
    // We need balance to stay <= final_b => must delete enough C's to lower max balance
    //   => delete max(0, max_b - final_b) characters
    //
    // But these deletions interact. The answer is:
    // max(0, -min_b) + max(0, max_b - final_b)
    // but we need to check if they overlap (they shouldn't since one deletes T's and other C's).
    //
    // Actually this IS the answer for the subsequence problem!
    // Because: to fix prefix condition, delete T's (which raises balance).
    // To fix suffix condition, delete C's (which lowers balance).
    // These are independent deletions of different character types.
    //
    // So answer = max(0, -min_b) + max(0, max_b - final_b)
    // But wait, after deleting T's to fix prefix, the balance changes,
    // which affects the suffix condition. Hmm.
    //
    // Let me reconsider. For the ORIGINAL string (not subsequence):
    // min deletions = max(0, -min_b) + max(0, max_b - final_b)
    // This is because: delete T's at positions where balance would go negative
    // (raises min_b to 0), and delete C's at positions where balance exceeds final_b
    // (lowers max_b to final_b).
    //
    // For the subsequence, we can be smarter. But I think the same formula applies
    // because the deletions are of different character types and don't interfere.

    // Precompute prefix sums
    vector<int> prefix(N + 1, 0);
    for (int i = 0; i < N; i++)
        prefix[i + 1] = prefix[i] + (S[i] == 'C' ? 1 : -1);

    // Sparse table for range min and max of prefix[]
    int LOG = 20;
    vector<vector<int>> st_min(LOG, vector<int>(N + 1));
    vector<vector<int>> st_max(LOG, vector<int>(N + 1));
    for (int i = 0; i <= N; i++) {
        st_min[0][i] = prefix[i];
        st_max[0][i] = prefix[i];
    }
    for (int j = 1; j < LOG; j++)
        for (int i = 0; i + (1 << j) <= N + 1; i++) {
            st_min[j][i] = min(st_min[j-1][i], st_min[j-1][i + (1 << (j-1))]);
            st_max[j][i] = max(st_max[j-1][i], st_max[j-1][i + (1 << (j-1))]);
        }

    auto range_min = [&](int l, int r) -> int {
        int k = 31 - __builtin_clz(r - l + 1);
        return min(st_min[k][l], st_min[k][r - (1 << k) + 1]);
    };
    auto range_max = [&](int l, int r) -> int {
        int k = 31 - __builtin_clz(r - l + 1);
        return max(st_max[k][l], st_max[k][r - (1 << k) + 1]);
    };

    while (Q--) {
        int L, R;
        cin >> L >> R;
        // min_b = min prefix[i] for i in [L-1, R] relative to prefix[L-1]
        int min_b = range_min(L - 1, R) - prefix[L - 1];
        int max_b = range_max(L - 1, R) - prefix[L - 1];
        int final_b = prefix[R] - prefix[L - 1];
        int ans = max(0, -min_b) + max(0, max_b - final_b);
        cout << ans << "\n";
    }
    return 0;
}
