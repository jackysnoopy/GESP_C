#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int MAXN = 1000005;
int h[MAXN], v[MAXN];
int parent[MAXN];
vector<int> children[MAXN];
int n;

void dfs(int u) {
    for (int child : children[u]) {
        dfs(child);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n;
    
    for (int i = 2; i <= n; i++) {
        cin >> parent[i];
        children[parent[i]].push_back(i);
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }
    
    // Simplified approach
    long long ans = 0;
    int step = 1;
    
    // Process in topological order
    vector<int> order;
    vector<int> in_degree(n + 1, 0);
    
    for (int i = 2; i <= n; i++) {
        in_degree[i]++;
    }
    
    // BFS from root
    vector<int> queue;
    queue.push_back(1);
    
    while (!queue.empty()) {
        int u = queue.front();
        queue.erase(queue.begin());
        order.push_back(u);
        
        for (int v : children[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                queue.push_back(v);
            }
        }
    }
    
    // Process each node
    for (int u : order) {
        if (u == 1) continue;
        
        // Calculate ratio for subtree
        long long total_h = h[u];
        long long total_v = v[u];
        
        for (int child : children[u]) {
            total_h += h[child];
            total_v += v[child];
        }
        
        long long ratio = (total_h + total_v - 1) / total_v;
        ans += step * ratio;
        step++;
    }
    
    cout << ans << endl;
    
    return 0;
}