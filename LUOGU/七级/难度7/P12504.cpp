#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
vector<int> adj[MAXN];
int depth[MAXN];
int parent[MAXN];

void dfs(int u, int p, int d) {
    parent[u] = p;
    depth[u] = d;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    int d;
    cin >> d;
    
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, 0, 0);
    
    // 树上的青蛙问题
    // 青蛙初始为绿色，每次跳跃颜色切换
    // 需要配对绿色和棕色青蛙，跳跃次数为奇数且不超过d
    
    // 简单贪心：按深度排序，配对深度差为奇数的青蛙
    vector<int> nodes(n);
    for (int i = 0; i < n; i++) nodes[i] = i + 1;
    
    sort(nodes.begin(), nodes.end(), [&](int a, int b) {
        return depth[a] < depth[b];
    });
    
    vector<bool> used(n + 1, false);
    vector<pair<int, int>> pairs;
    
    for (int i = 0; i < n; i++) {
        if (used[nodes[i]]) continue;
        
        for (int j = i + 1; j < n; j++) {
            if (used[nodes[j]]) continue;
            
            int dist = depth[nodes[i]] + depth[nodes[j]] - 2 * depth[parent[nodes[i]]];
            if (dist % 2 == 1 && dist <= d) {
                pairs.push_back({nodes[i], nodes[j]});
                used[nodes[i]] = true;
                used[nodes[j]] = true;
                break;
            }
        }
    }
    
    cout << pairs.size() << "\n";
    for (auto& [u, v] : pairs) {
        cout << u << " " << v << "\n";
    }
    
    return 0;
}
