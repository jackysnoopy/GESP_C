#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> a(n+1), b(m+1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int j = 1; j <= m; j++) cin >> b[j];
    vector<int> sa(n+1,0), sb(m+1,0);
    for (int i = 1; i <= n; i++) sa[i]=sa[i-1]+a[i];
    for (int j = 1; j <= m; j++) sb[j]=sb[j-1]+b[j];
    const long long INF = 1e18;
    vector<vector<long long>> dp(n+1, vector<long long>(m+1, INF));
    dp[0][0] = 0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (dp[i][j] >= INF) continue;
            for (int di = 1; di <= n-i; di++)
                for (int dj = 1; dj <= m-j; dj++) {
                    long long s1=sa[i+di]-sa[i], s2=sb[j+dj]-sb[j];
                    long long cost=(s2-dj)*(s1-di);
                    dp[i+di][j+dj]=min(dp[i+di][j+dj],dp[i][j]+cost);
                }
        }
    cout << dp[n][m] << endl;
    return 0;
}