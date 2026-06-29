#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
vector<int> tree[MAXN];
int dp[MAXN][3]; // 0:自己是消防局, 1:被子节点覆盖, 2:被孙子节点覆盖

void dfs(int u, int fa) {
    dp[u][0] = 1;
    dp[u][1] = MAXN;
    dp[u][2] = 0;
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        dp[u][0] += min(dp[v][0], min(dp[v][1], dp[v][2]));
        dp[u][2] += min(dp[v][1], dp[v][2]);
    }
    
    int min1 = MAXN, min2 = MAXN;
    for (int v : tree[u]) {
        if (v == fa) continue;
        int val = dp[v][0] - min(dp[v][1], dp[v][2]);
        if (val < min1) {
            min2 = min1;
            min1 = val;
        } else if (val < min2) {
            min2 = val;
        }
    }
    
    if (min1 < MAXN) dp[u][1] = dp[u][2] + min1;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        tree[i].push_back(p);
        tree[p].push_back(i);
    }
    
    dfs(1, 0);
    printf("%d\n", min(dp[1][0], dp[1][1]));
    
    return 0;
}
