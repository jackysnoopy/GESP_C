#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    string t, s;
    cin >> t >> s;
    
    // T的非空前缀是合法魔法词缀
    // 将S分成最少的魔法词缀
    
    // DP：dp[i] = 将S[0..i-1]划分的最少段数
    // dp[0] = 0
    // 对于每个位置i，尝试所有可能的上一段结尾j
    // 如果S[j..i-1]是T的前缀，则dp[i] = min(dp[i], dp[j]+1)
    
    // 优化：预处理每个位置i，S[i..]与T的最长公共前缀
    // 用KMP或Z算法
    
    // 简单方法：对每个位置i，找S[i..]与T的最长匹配
    vector<int> lcp(m);
    for (int i = 0; i < m; i++) {
        int len = 0;
        while (i + len < m && len < n && s[i + len] == t[len]) {
            len++;
        }
        lcp[i] = len;
    }
    
    vector<int> dp(m + 1, m + 1);
    dp[0] = 0;
    
    for (int i = 0; i < m; i++) {
        if (dp[i] > m) continue;
        for (int len = 1; len <= lcp[i]; len++) {
            dp[i + len] = min(dp[i + len], dp[i] + 1);
        }
    }
    
    if (dp[m] > m) cout << "Fake\n";
    else cout << dp[m] << "\n";
    
    return 0;
}
