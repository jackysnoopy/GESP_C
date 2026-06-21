#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, L;
    cin >> n >> L;
    
    const long long INF = 1e18;
    vector<long long> dp(L + 1, INF);
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        int c, l;
        cin >> c >> l;
        for (int v = L - 1; v >= 0; v--) {
            if (dp[v] == INF) continue;
            int nv = min(L, v + l);
            dp[nv] = min(dp[nv], dp[v] + c);
        }
    }
    
    if (dp[L] == INF) {
        cout << "no solution\n";
    } else {
        cout << dp[L] << "\n";
    }
    
    return 0;
}
