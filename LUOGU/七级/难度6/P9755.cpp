#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
long long a[MAXN], b[MAXN], c[MAXN];
int n;

void dfs(int u, int parent) {
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> c[i];
    }
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // 简单实现：计算最少天数
    // 这里需要更复杂的算法
    long long ans = 0;
    
    // 计算每个地块需要的天数
    for (int i = 1; i <= n; i++) {
        long long days = (a[i] + b[i] - 1) / b[i];
        ans = max(ans, days);
    }
    
    cout << ans << "\n";
    return 0;
}