#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int E, F;
        cin >> E >> F;
        int W = F - E;
        int N;
        cin >> N;
        vector<int> weight(N), value(N);
        for (int i = 0; i < N; i++) cin >> value[i] >> weight[i];
        const int INF = 1e9;
        vector<int> dp(W + 1, INF);
        dp[0] = 0;
        for (int i = 0; i < N; i++) {
            for (int j = weight[i]; j <= W; j++) {
                if (dp[j - weight[i]] + 1 < dp[j]) {
                    dp[j] = dp[j - weight[i]] + 1;
                }
            }
        }
        if (dp[W] < INF) cout << "The minimum amount of money in the piggy-bank is " << dp[W] << " cents.\n";
        else cout << "This is impossible.\n";
    }
    return 0;
}
