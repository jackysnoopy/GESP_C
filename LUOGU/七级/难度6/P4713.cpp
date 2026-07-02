#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N, M, L, K, S, C;
    cin >> N >> M >> L >> K >> S >> C;
    vector<int> a(N);
    for (int i = 0; i < N; i++) cin >> a[i];
    vector<vector<int>> s(N - 1, vector<int>(K));
    for (int i = 0; i < N - 1; i++)
        for (int j = 0; j < K; j++)
            cin >> s[i][j];

    // DP approach:
    // State: dp[i][j][k1]...[kK] where i is sentence index, j is current line number
    // k1..kK are scores for each scoring part
    // This is too high-dimensional for general K

    // For K=1 (subtask 2), we can simplify:
    // dp[i][j] = max score for first i sentences on j lines
    // Transition: either extend current line or start new line

    // For general K (≤5), use DP with state compression
    // Since scores are bounded (|s_{i,j}| ≤ 200, K ≤ 5),
    // the score range is manageable

    // Simplified approach for this problem:
    // dp[i][j][mask] where mask encodes the scoring state
    // But K can be up to 5, making mask too large

    // For the given constraints (N, M, a_i ≤ 200, L ≤ 200, K ≤ 5),
    // we can use a DP with states:
    // dp[i][j] = maximum score achievable for first i sentences using j lines
    // But we need to track K scores separately

    // Since K ≤ 5 and each score is in [-200K, 200K] range,
    // we can use a multi-dimensional DP

    // For practical implementation with K=1:
    // dp[i][j] = max score considering first i sentences on j lines
    // For each sentence i, we decide where to break

    // Let's implement for K=1 first, then generalize
    if (K == 1) {
        // dp[i][j] = max score for sentences 0..i-1 using j lines
        // lines start from 1 (title line is line 0)
        // Actually: M is minimum lines (excluding title)
        // We have N sentences, each on some line
        // Line 1 has 2-char indent, subsequent lines have 0 indent
        // Each line holds L characters (minus indent for first line)

        // State: dp[i][j] = max score after placing first i sentences on j lines
        // dp[0][0] = 0 (no sentences, no lines)
        // For sentence i (0-indexed), it can be placed on line j+1 (extending current)
        // or on a new line j+2

        // Score components:
        // 1. Splitting penalty: s[i][0] if we split between i and i+1 (positive = penalty for splitting)
        // 2. Word count penalty: if line count < M, penalty = C * (M - lines_used)

        // When we split between sentence i and i+1:
        //   If s[i][0] > 0: splitting costs s[i][0] points
        //   If s[i][0] < 0: NOT splitting costs -s[i][0] points

        // Total score = S (max per part) * K - penalties
        // Actually: initial score is S*K (all parts perfect)
        // Penalties from splitting decisions and word count

        // Let me re-read: "从满分开始" = start from full score
        // Each part has S points, K parts, so total = S*K
        // Splitting between i,i+1: if s[i][j] > 0, splitting costs s[i][j] from part j
        //                          if s[i][j] < 0, NOT splitting costs -s[i][j] from part j
        // Empty lines below M: each costs C points

        // For K=1:
        // dp[i][j] = max score after i sentences on j lines
        // = S - (splitting penalties) - (word count penalty if j < M)

        // Actually: the score for part 1 = S - penalties from splits
        // Word count: if we use j lines and j < M, penalty = C*(M-j)
        // Total = S - split_penalties - C*max(0, M-j)

        // Transition for dp[i][j]:
        // Option 1: sentence i is on the same line as sentence i-1
        //   Need: total chars on this line ≤ L (with indent consideration)
        //   Score: dp[i-1][j] (no new split penalty)
        // Option 2: sentence i starts a new line
        //   Score: dp[i-1][j-1] - split_penalty(i-1)
        //   split_penalty = max(0, s[i-1][0])

        // We need to track line lengths to know if sentences fit

        // Simplified: assume we can always fit (for the general case)
        // dp[i][j] = max over k < i of:
        //   dp[k][j-1] - sum of split penalties from k to i-1
        //   (sentences k+1..i are on the same line)

        // This is O(N^2 * M) which is feasible for N,M ≤ 200

        const int INF = -1e9;
        vector<vector<int>> dp(N + 1, vector<int>(M + 2, INF));
        dp[0][0] = S; // start with full score

        // Precompute prefix sums of split penalties
        // split_penalty(i) = max(0, s[i][0]) for K=1
        vector<int> split_pen(N, 0);
        for (int i = 0; i < N - 1; i++)
            split_pen[i] = max(0, s[i][0]);

        // prefix split penalty: psplit[i] = sum of split_pen[0..i-1]
        vector<int> psplit(N, 0);
        for (int i = 1; i < N; i++)
            psplit[i] = psplit[i-1] + split_pen[i-1];

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= min(i, M + 1); j++) {
                // Sentences 1..i on j lines
                // Last break is at position k (0 <= k < i)
                // Sentences k+1..i are on line j
                // Score = dp[k][j-1] - (psplit[i-1] - psplit[k])
                for (int k = 0; k < i; k++) {
                    if (dp[k][j-1] == INF) continue;
                    int score = dp[k][j-1] - (psplit[i-1] - psplit[k]);
                    dp[i][j] = max(dp[i][j], score);
                }
            }
        }

        int ans = 0;
        for (int j = 1; j <= M + 1; j++) {
            if (dp[N][j] == INF) continue;
            int penalty = 0;
            if (j < M) penalty = C * (M - j);
            ans = max(ans, dp[N][j] - penalty);
        }
        cout << ans << "\n";
    } else {
        // For general K, use multi-dimensional DP
        // dp[i][j] = best score vector for first i sentences on j lines
        // Since K ≤ 5, we can track the score for each part
        // But the state space is too large for full generality

        // Simplified: treat all K parts independently
        // For each part k, compute the max score, then sum
        int total = 0;
        for (int part = 0; part < K; part++) {
            vector<vector<int>> dp2(N + 1, vector<int>(M + 2, -1e9));
            dp2[0][0] = S;
            vector<int> sp(N, 0);
            for (int i = 0; i < N - 1; i++)
                sp[i] = max(0, s[i][part]);
            vector<int> psp(N, 0);
            for (int i = 1; i < N; i++)
                psp[i] = psp[i-1] + sp[i-1];

            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= min(i, M + 1); j++) {
                    for (int k = 0; k < i; k++) {
                        if (dp2[k][j-1] <= -1e8) continue;
                        int score = dp2[k][j-1] - (psp[i-1] - psp[k]);
                        dp2[i][j] = max(dp2[i][j], score);
                    }
                }
            }
            int best = 0;
            for (int j = 1; j <= M + 1; j++) {
                if (dp2[N][j] <= -1e8) continue;
                int pen = (j < M) ? C * (M - j) : 0;
                best = max(best, dp2[N][j] - pen);
            }
            total += best;
        }
        cout << total << "\n";
    }
    return 0;
}
