#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    const int INF = 1e9;
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    
    for (int j = 1; j * j <= n; j++) {
        int sq = j * j;
        for (int i = sq; i <= n; i++) {
            dp[i] = min(dp[i], dp[i - sq] + 1);
        }
    }
    
    cout << dp[n] << endl;
    return 0;
}
