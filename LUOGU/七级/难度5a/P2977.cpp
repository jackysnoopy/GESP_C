#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
vector<int> tree[MAXN];
int n, k;
int ans;

int dfs(int u, int fa) {
    vector<int> vals;
    
    for (int v : tree[u]) {
        if (v == fa) continue;
        int val = dfs(v, u);
        vals.push_back(val);
    }
    
    if (vals.empty()) return 1;
    
    sort(vals.begin(), vals.end(), greater<int>());
    
    // 贪心匹配
    int matched = 0;
    for (int i = 0; i < (int)vals.size(); i++) {
        if (vals[i] > 0 && matched < k) {
            ans++;
            matched++;
            vals[i]--;
        }
    }
    
    // 返回未匹配的
    int total = 0;
    for (int v : vals) total += v;
    
    return total;
}

int main() {
    scanf("%d%d", &n, &k);
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    
    ans = 0;
    dfs(1, 0);
    
    printf("%d\n", ans);
    
    return 0;
}
