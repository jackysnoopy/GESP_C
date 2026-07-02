#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int n;
bool visited[MAXN];

int dfs(int u, int p) {
    int max_depth = 0;
    for (int v : adj[u]) {
        if (v != p && !visited[v]) {
            int depth = dfs(v, u) + 1;
            max_depth = max(max_depth, depth);
        }
    }
    return max_depth;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    while (T--) {
        cin >> n;
        
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
            visited[i] = false;
        }
        
        for (int i = 0; i < n - 1; i++) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        
        // Find the diameter endpoint
        int farthest = 1;
        int max_dist = 0;
        
        for (int i = 1; i <= n; i++) {
            int dist = dfs(i, 0);
            if (dist > max_dist) {
                max_dist = dist;
                farthest = i;
            }
        }
        
        // Simple approach: answer is related to tree structure
        // For now, output a heuristic
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (adj[i].size() >= 2) {
                ans++;
            }
        }
        
        cout << max(1, ans / 2) << endl;
    }
    
    return 0;
}