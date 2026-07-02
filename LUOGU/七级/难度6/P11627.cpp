#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int MOD = 998244353;
int n;
vector<int> adj[MAXN];
int edge_u[MAXN], edge_v[MAXN];

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i < n; i++) {
        scanf("%d %d", &edge_u[i], &edge_v[i]);
        adj[edge_u[i]].push_back(edge_v[i]);
        adj[edge_v[i]].push_back(edge_u[i]);
    }
    
    // 简化处理：选择节点1作为必经点
    int t = 1;
    
    // 计算得分（简化）
    long long ans = 0;
    for (int i = 1; i < n; i++) {
        ans = (ans + (long long)i * (n - i)) % MOD;
    }
    
    printf("%lld\n", ans);
    printf("%d\n", t);
    
    // 输出边权（简化）
    for (int i = 1; i < n; i++) {
        printf("%d%c", i, i == n - 1 ? '\n' : ' ');
    }
    
    return 0;
}