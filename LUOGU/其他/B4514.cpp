#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    // DP: dp[j] = maximum code ability after eating some red apples and j gold apples.
    // Gold apples double ability. Red apples add/subtract.
    // Process red apples in order. Between red apples, we can eat gold apples.
    //
    // dp[j] = max ability with j gold apples eaten so far.
    // Initially: dp[0] = 1, dp[j] = -inf for j > 0.
    // For each red apple a[i]:
    //   For j from m down to 0: dp[j] += a[i] (eat red apple)
    //   Then, we can eat gold apples: dp[j] = max over k<=j of (dp[k] * 2^(j-k))
    //   But this is expensive. Instead, we can eat gold apples BEFORE the red apple.
    //
    // Actually, the order is: we eat red apples in order, and gold apples can be
    // eaten at any time (before, between, or after red apples).
    //
    // Let me think of it as: we have n red apples in order and m gold apples.
    // We can interleave them arbitrarily (red in order, gold anywhere).
    // Each gold apple doubles current ability.
    // Each red apple adds a[i] to ability.
    // Maximize final ability.
    //
    // DP: dp[j] = max ability after processing some prefix of red apples, with j gold apples used.
    // For each red apple a[i]:
    //   For j from 0 to m: dp_new[j] = dp[j] + a[i] (eat red apple with j gold apples already used)
    //   But we can also eat gold apples AFTER the red apple:
    //   For j from 1 to m: dp[j] = max(dp[j], dp[j-1] * 2) (eat one more gold apple)
    //   
    // Wait, the gold apples can be eaten at any time. So for each state (i, j),
    // we can:
    // 1. Eat the next red apple: dp[i+1][j] = dp[i][j] + a[i]
    // 2. Eat a gold apple: dp[i][j+1] = dp[i][j] * 2
    //
    // This is a 2D DP. But n <= 1e5 and m <= 20, so we can optimize.
    //
    // dp[j] = max ability after processing some prefix, with j gold apples used.
    // Process red apples one by one:
    // For each red apple a[i]:
    //   For j from m down to 0: dp[j] += a[i] (eat red apple)
    //   Then for j from 0 to m-1: dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold apple)
    //   But this is wrong because we might want to eat gold apples BEFORE the red apple.
    //
    // Correct approach: for each red apple, we can eat 0 or more gold apples before it,
    // then eat the red apple.
    //
    // dp[j] = max ability after processing some prefix of red apples, with j gold apples used.
    // For each red apple a[i]:
    //   For j from 0 to m: dp[j] += a[i] (eat red apple)
    //   For j from 0 to m-1: dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold apple after red apple)
    //   But we also need to consider eating gold apples BEFORE the red apple.
    //
    // Actually, the order of gold and red apples matters because gold doubles.
    // Doubling a larger number is better. So we should eat gold apples when ability is high.
    //
    // Optimal strategy: eat all red apples first (to maximize ability), then eat all gold apples.
    // But we can interleave: eat some red, then gold, then more red, then gold, etc.
    //
    // Since gold doubles, we want to double when ability is highest. So eat gold last.
    // But red apples can be negative, so eating gold before negative red might be bad.
    //
    // DP: dp[j] = max ability after processing red apples 0..i, with j gold apples used.
    // For each red apple a[i]:
    //   Option 1: eat red first, then gold. dp[j] += a[i] for all j.
    //   Option 2: eat gold first, then red. dp[j+1] = max(dp[j+1], dp[j]*2 + a[i]).
    //   But option 2 is covered by: eat gold (dp[j] -> dp[j]*2), then eat red (dp[j]*2 -> dp[j]*2 + a[i]).
    //
    // So the DP is:
    // For each red apple a[i]:
    //   For j from m down to 0: dp[j] += a[i]
    //   For j from 0 to m-1: dp[j+1] = max(dp[j+1], dp[j] * 2)
    //
    // Wait, but this processes gold AFTER red. We also need gold BEFORE red.
    // The issue: if we eat gold before red, the gold multiplies a larger number.
    //
    // Let me think again. The DP state is: after processing red apples 0..i, with j gold apples used.
    // Transitions:
    // 1. Eat red apple i+1: dp[i+1][j] = dp[i][j] + a[i+1]
    // 2. Eat a gold apple: dp[i][j+1] = dp[i][j] * 2
    //
    // So for each i, we first try eating gold, then eating red.
    // In 1D DP: for each red apple a[i]:
    //   For j from 0 to m-1: dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold before red)
    //   For j from 0 to m: dp[j] += a[i] (eat red)
    //
    // Let me verify with sample 1: n=6, m=2, a=[1,-2,3,1,-6,5].
    // dp = [1, -inf, -inf]
    // Red a[0]=1:
    //   Gold: dp[1] = max(-inf, 1*2) = 2. dp = [1, 2, -inf].
    //   Red: dp[0]+=1=2, dp[1]+=1=3, dp[2]+=-inf. dp = [2, 3, -inf].
    // Red a[1]=-2:
    //   Gold: dp[1]=max(3, 2*2)=4. dp[2]=max(-inf, 3*2)=6. dp = [2, 4, 6].
    //   Red: dp[0]+=(-2)=0, dp[1]+=(-2)=2, dp[2]+=(-2)=4. dp = [0, 2, 4].
    // Red a[2]=3:
    //   Gold: dp[1]=max(2, 0*2)=2. dp[2]=max(4, 2*2)=4. dp = [0, 2, 4].
    //   Red: dp[0]+=3=3, dp[1]+=3=5, dp[2]+=3=7. dp = [3, 5, 7].
    // Red a[3]=1:
    //   Gold: dp[1]=max(5, 3*2)=6. dp[2]=max(7, 5*2)=10. dp = [3, 6, 10].
    //   Red: dp[0]+=1=4, dp[1]+=1=7, dp[2]+=1=11. dp = [4, 7, 11].
    // Red a[4]=-6:
    //   Gold: dp[1]=max(7, 4*2)=8. dp[2]=max(11, 7*2)=14. dp = [4, 8, 14].
    //   Red: dp[0]+=-6=-2, dp[1]+=-6=2, dp[2]+=-6=8. dp = [-2, 2, 8].
    // Red a[5]=5:
    //   Gold: dp[1]=max(2, -2*2)=2. dp[2]=max(8, 2*2)=8. dp = [-2, 2, 8].
    //   Red: dp[0]+=5=3, dp[1]+=5=7, dp[2]+=5=13. dp = [3, 7, 13].
    // Answer: max(dp) = 13. But expected is 15!
    //
    // So my DP is wrong. Let me reconsider.
    //
    // The issue: gold apples should be eaten when ability is highest, not before every red apple.
    // The DP should allow eating gold apples at any point, not just before red apples.
    //
    // Correct DP: process red apples in order. For each state, we can:
    // 1. Eat the next red apple.
    // 2. Eat a gold apple (at any time).
    //
    // In 1D DP with j gold apples used:
    // For each red apple a[i]:
    //   For j from 0 to m: dp[j] += a[i] (eat red)
    // Then, for j from 0 to m-1: dp[j+1] = max(dp[j+1], dp[j]*2) (eat gold)
    //
    // But this processes ALL red apples first, then gold. That's wrong because
    // we might want to eat gold between red apples.
    //
    // The correct approach: for each red apple, we can eat 0 or more gold apples before it.
    // So the DP should be:
    // For each red apple a[i]:
    //   For j from m down to 0:
    //     dp[j] += a[i] (eat red apple with j gold apples already used)
    //   For j from 0 to m-1:
    //     dp[j+1] = max(dp[j+1], dp[j] * 2) (eat one more gold apple)
    //
    // But this processes gold AFTER red for each step. We also need gold BEFORE red.
    //
    // Actually, the correct order is:
    // For each red apple a[i]:
    //   For j from 0 to m-1:
    //     dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold before red)
    //   For j from 0 to m:
    //     dp[j] += a[i] (eat red)
    //
    // But we also need to consider eating gold AFTER red. So:
    // For each red apple a[i]:
    //   For j from 0 to m-1:
    //     dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold)
    //   For j from 0 to m:
    //     dp[j] += a[i] (eat red)
    //   For j from 0 to m-1:
    //     dp[j+1] = max(dp[j+1], dp[j] * 2) (eat gold again)
    //
    // This allows eating gold before AND after each red apple.
    // But this might allow eating gold multiple times between red apples, which is correct!
    
    // Let me redo with this approach:
    vector<long long> dp(m + 1, -1e18);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        // Eat gold apples (can eat multiple)
        for (int j = 0; j < m; j++) {
            dp[j+1] = max(dp[j+1], dp[j] * 2);
        }
        // Eat red apple
        for (int j = 0; j <= m; j++) {
            dp[j] += a[i];
        }
    }
    // Eat remaining gold apples
    for (int j = 0; j < m; j++) {
        dp[j+1] = max(dp[j+1], dp[j] * 2);
    }
    long long ans = -1e18;
    for (int j = 0; j <= m; j++) ans = max(ans, dp[j]);
    cout << ans << "\n";
    return 0;
}
