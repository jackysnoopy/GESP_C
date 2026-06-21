#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1000005;
vector<int> children[MAXN];
int dp[MAXN][2];
void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    int maxGain = 0;
    for (int v : children[u]) {
        dfs(v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        maxGain = max(maxGain, dp[v][1] - dp[v][0]);
    }
    dp[u][1] = 1 + dp[u][0] - maxGain;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int p;
        cin >> p;
        children[p].push_back(i);
    }
    dfs(0);
    cout << max(dp[0][0], dp[0][1]) << endl;
    return 0;
}