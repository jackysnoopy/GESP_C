#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> c(n + 1), a(n + 1);
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i <= n; i++) cin >> a[i];
    sort(c.begin() + 1, c.end());
    
    // dp[i][j][t]: max score for first i students (sorted by c),
    // j open groups (have min but not max yet), total size of open groups = t
    // When closing a group of current size s: add a[s+1] + c[i] - (c[min] already counted when opening)
    const long long NEG = LLONG_MIN / 2;
    // Use rolling array on i
    vector<vector<vector<long long>>> dp(2, vector<vector<long long>>(n + 1, vector<long long>(n + 1, NEG)));
    dp[0][0][0] = 0;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        int nxt = 1 - cur;
        for (int j = 0; j <= n; j++)
            for (int t = 0; t <= n; t++)
                dp[nxt][j][t] = NEG;
        
        for (int j = 0; j <= i; j++) {
            for (int t = j; t <= i; t++) {
                if (dp[cur][j][t] == NEG) continue;
                long long val = dp[cur][j][t];
                long long ci = c[i + 1];
                
                // 1. Solo: student i+1 is a group of size 1
                dp[nxt][j][t] = max(dp[nxt][j][t], val + a[1]);
                
                // 2. Open new group: student i+1 is min, -c[i+1] contribution
                dp[nxt][j+1][t+1] = max(dp[nxt][j+1][t+1], val - ci);
                
                // 3. Close a group of size s: student i+1 is max
                if (j > 0) {
                    int maxS = t - (j - 1);
                    for (int s = 1; s <= maxS; s++) {
                        dp[nxt][j-1][t-s] = max(dp[nxt][j-1][t-s], val + ci + a[s+1]);
                    }
                }
                
                // 4. Middle: add to existing open group
                if (j > 0) {
                    dp[nxt][j][t+1] = max(dp[nxt][j][t+1], val);
                }
            }
        }
        cur = nxt;
    }
    
    cout << dp[cur][0][0] << "\n";
    return 0;
}
