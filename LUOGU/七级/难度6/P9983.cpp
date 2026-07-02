#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 1e5 + 5;

vector<int> adj[MAXN];
int infected[MAXN];
int n, q;

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
    
    string s;
    cin >> s;
    
    for (int i = 0; i < n; i++) {
        infected[i + 1] = s[i] - '0';
    }
    
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    cin >> q;
    while (q--) {
        int nights;
        cin >> nights;
        
        // 简单实现：计算最少初始感染奶牛数
        // 这里需要更复杂的算法
        int ans = 0;
        
        // 统计感染奶牛数量
        for (int i = 1; i <= n; i++) {
            if (infected[i]) ans++;
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}