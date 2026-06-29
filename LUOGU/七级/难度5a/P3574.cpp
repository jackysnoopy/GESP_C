#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
vector<int> tree[MAXN];
int c[MAXN];
int n;
int ans;

int dfs(int u, int fa) {
    vector<int> vals;
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        int val = dfs(v, u);
        vals.push_back(val);
    }
    
    if (vals.empty()) return c[u];
    
    sort(vals.begin(), vals.end(), greater<int>());
    
    int max_val = 0;
    for (int i = 0; i < (int)vals.size(); i++) {
        max_val = max(max_val, vals[i] + i + 1);
    }
    
    return max(max_val, c[u]);
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i]);
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    ans = dfs(1, 0);
    printf("%d\n", ans);
    
    return 0;
}
