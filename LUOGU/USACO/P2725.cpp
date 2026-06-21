#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[2000005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int S, C;
    cin >> S >> C;
    vector<int> stamps(C);
    for (int i = 0; i < C; i++) cin >> stamps[i];
    // BFS/DP: min stamps to make each value
    for (int i = 1; i <= S; i++) dp[i] = 1e9;
    for (int i = 0; i < C; i++)
        if (stamps[i] <= S) dp[stamps[i]] = 1;
    for (int i = 1; i <= S; i++) {
        if (dp[i] == 1e9) continue;
        for (int j = 0; j < C; j++) {
            int nxt = i + stamps[j];
            if (nxt <= S) dp[nxt] = min(dp[nxt], dp[i] + 1);
        }
    }
    cout << dp[S] << "\n";
    return 0;
}
