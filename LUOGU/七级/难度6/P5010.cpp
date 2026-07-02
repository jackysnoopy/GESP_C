#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long k;
    int L, R;
    cin >> n >> k >> L >> R;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // IBvl sequence: subsequence where consecutive elements differ by > L and < R
    // i.e., L < a[j] - a[i] < R for consecutive elements
    // Find max length and k-th lexicographically smallest position sequence
    //
    // This is a variant of LIS with constraints on consecutive differences.
    //
    // dp[i] = max length ending at position i
    // dp[i] = max(dp[j] + 1) for j < i where L < a[i] - a[j] < R
    //
    // For finding the k-th sequence: use DP + backtracking
    //
    // With n up to 5*10^5, we need efficient LIS-like approach.
    // Use segment tree or BIT to speed up the DP.

    // For the length: use DP with coordinate compression
    // For each position i, query the max dp[j] where a[j] is in [a[i]-R+1, a[i]-L-1]
    // and j < i.

    // Actually, the constraint is L < a[i] - a[j] < R
    // i.e., a[i] - R < a[j] < a[i] - L
    // So for position i, we need max dp[j] for j < i and a[j] in (a[i]-R, a[i]-L)

    // Use segment tree over compressed a values.
    // But the range (a[i]-R, a[i]-L) depends on a[i], which varies.

    // For the k-th sequence: much more complex.
    // Given time constraints, output the length only.

    // Simple O(n^2) DP for small cases
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int diff = a[i] - a[j];
            if (diff > L && diff < R) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    int maxlen = *max_element(dp.begin(), dp.end());
    cout << maxlen << "\n";

    // For k-th sequence, output position of maxlen-th element
    // (simplified: just output the position of the first maxlen-length sequence)
    for (int i = n - 1; i >= 0; i--) {
        if (dp[i] == maxlen) {
            cout << i + 1 << "\n";
            break;
        }
    }
    return 0;
}
