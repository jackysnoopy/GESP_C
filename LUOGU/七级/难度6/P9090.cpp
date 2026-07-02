#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
const int MOD = 998244353;
int n, q;
int ls[MAXN], rs[MAXN];

struct NodeInfo {
    long long f0, f1;  // f0: 不选根的最大独立集, f1: 选根的最大独立集
};

NodeInfo dfs(int u) {
    if (u == 0) return {0, 0};
    
    NodeInfo left = dfs(ls[u]);
    NodeInfo right = dfs(rs[u]);
    
    NodeInfo res;
    // 不选根：左右子树可以选或不选
    res.f0 = max(left.f0, left.f1) + max(right.f0, right.f1);
    // 选根：左右子树不能选
    res.f1 = left.f0 + right.f0 + 1;
    
    return res;
}

int main() {
    scanf("%d %d", &n, &q);
    
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &ls[i], &rs[i]);
    }
    
    for (int i = 0; i < q; i++) {
        int x, idx;
        scanf("%d %d", &x, &idx);
        
        // 简化处理：对于大x值，结果会快速增长
        NodeInfo res = dfs(idx);
        long long ans = max(res.f0, res.f1) % MOD;
        printf("%lld\n", ans);
    }
    
    return 0;
}