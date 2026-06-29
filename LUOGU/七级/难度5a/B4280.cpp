#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    const int MAXV = 100;
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    
    int ans = 0;
    for (int v = 1; v <= MAXV; v++) {
        int cur = v & 1;
        int pre = 1 - cur;
        
        for (int i = 1; i <= n; i++) {
            dp[cur][i] = (a[i] == v) ? i : 0;
        }
        
        for (int i = 1; i <= n; i++) {
            if (dp[pre][i] > 0) {
                int j = dp[pre][i] + 1;
                if (j <= n && dp[pre][j] > 0) {
                    dp[cur][i] = max(dp[cur][i], dp[pre][j]);
                }
            }
            if (dp[cur][i] > 0) ans = v;
        }
    }
    
    cout << ans << endl;
    return 0;
}
