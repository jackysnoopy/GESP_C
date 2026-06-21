#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;
    
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    const long long INF = 4e18;
    vector<long long> dp(n + 1, -INF);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        int cnt[26] = {0};
        for (int j = i - 1; j >= max(0, i - 26); j--) {
            int idx = s[j] - 'a';
            cnt[idx]++;
            if (cnt[idx] > 1) break;
            int len = i - j;
            if (dp[j] != -INF) {
                dp[i] = max(dp[i], dp[j] + a[len]);
            }
        }
    }
    
    cout << dp[n] << "\n";
    return 0;
}
