#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int n, k, t;
int depth[MAXN];
int ans;

void dfs(int u, int fa) {
    depth[u] = 0;
    int max_depth = -1;
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        depth[u] = max(depth[u], depth[v] + 1);
        max_depth = max(max_depth, depth[v] + 1);
    }
    
    if (max_depth >= k) {
        ans++;
        depth[u] = -1;
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &t);
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    ans = 0;
    dfs(1, 0);
    
    printf("%d\n", ans);
    
    return 0;
}
