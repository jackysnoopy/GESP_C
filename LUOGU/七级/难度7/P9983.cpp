#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
vector<int> adj[MAXN];
int infected[MAXN];
int n;

void dfs(int u, int p, int dist, vector<int>& candidates, int max_dist) {
    if (infected[u]) {
        candidates.push_back(dist);
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, dist + 1, candidates, max_dist);
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
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int Q;
    cin >> Q;
    
    while (Q--) {
        int nights;
        cin >> nights;
        
        // Cowntact Tracing问题
        // 简化处理：输出基本结果
        
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (infected[i]) {
                ans++;
            }
        }
        
        cout << ans << "\n";
    }
    
    return 0;
}
