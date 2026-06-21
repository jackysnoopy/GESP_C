#include <iostream>
#include <vector>
using namespace std;
vector<int> ch[500001];
long long a[500001];
int T_arr, C_val;
long long dp[500001][2];
void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = a[u];
    long long sum0 = 0, sum1 = 0;
    for (int v : ch[u]) {
        dfs(v);
        sum0 += dp[v][0];
        sum1 += min(dp[v][0], dp[v][1]);
    }
    dp[u][0] = sum1;
    dp[u][1] += sum0;
    // If u has parent and enough children write letters, u also writes
    // For the root (0), check if enough children write
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n >> T_arr >> C_val;
    for (int i = 1; i <= n; i++) {
        int p; cin >> p >> a[i];
        ch[p].push_back(i);
    }
    dfs(0);
    // For root (node 0): need >= ceil(C/T) children to write
    // Root's children that write = those where min(dp[v][0], dp[v][1]) == dp[v][1]
    // Actually this is more complex - need fractional knapsack like approach
    // Sort children by dp[v][1]-dp[v][0] (benefit of writing)
    int need = (C_val + T_arr - 1) / T_arr;
    vector<long long> diff;
    long long total0 = 0;
    for (int v : ch[0]) {
        total0 += dp[v][0];
        diff.push_back(dp[v][1] - dp[v][0]);
    }
    sort(diff.begin(), diff.end());
    long long best = total0;
    long long cur = total0;
    for (int i = 0; i < (int)diff.size(); i++) {
        cur += diff[i];
        if (i+1 >= need) best = min(best, cur);
    }
    cout << best << "\n";
    return 0;
}
