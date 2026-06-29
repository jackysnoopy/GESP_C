#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int a[MAXN];
int parent[MAXN];
int n;

void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    
    cin >> n;
    
    for (int i = 1; i <= 2 * n; i++) {
        cin >> a[i];
        adj[i].clear();
    }
    
    // 读入Alice选择的父亲
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        if (p > 0) {
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
    }
    
    // 构建树并DFS
    dfs(1, 0);
    
    // 输出DFS序列
    vector<int> result;
    vector<bool> visited(2 * n + 1, false);
    
    function<void(int)> dfsOrder = [&](int u) {
        visited[u] = true;
        result.push_back(a[u]);
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfsOrder(v);
            }
        }
    };
    
    dfsOrder(1);
    
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << "\n";
    
    return 0;
}
