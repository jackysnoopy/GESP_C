#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> children[MAXN];
long long f[MAXN];
long long dp[MAXN][2];

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = f[u];
    
    for (int v : children[u]) {
        dfs(v);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        int b;
        cin >> b;
        children[b].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> f[i];
    }
    
    dfs(1);
    
    cout << min(dp[1][0], dp[1][1]) << "\n";
    
    return 0;
}