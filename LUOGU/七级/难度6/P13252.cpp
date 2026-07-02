#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, M;
        cin >> N >> M;
        
        vector<string> zip(N);
        for (int i = 0; i < N; i++) cin >> zip[i];
        
        vector<vector<int>> adj(N);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        // 简化：按字典序贪心
        vector<bool> visited(N, false);
        string ans;
        
        // 从最小的ZIP码开始
        int start = 0;
        for (int i = 1; i < N; i++) {
            if (zip[i] < zip[start]) start = i;
        }
        
        visited[start] = true;
        ans = zip[start];
        
        // BFS/DFS 访问所有节点
        for (int step = 1; step < N; step++) {
            int next = -1;
            for (int i = 0; i < N; i++) {
                if (!visited[i]) {
                    // 检查是否可达
                    bool reachable = false;
                    for (int v : adj[i]) {
                        if (visited[v]) {
                            reachable = true;
                            break;
                        }
                    }
                    if (reachable && (next == -1 || zip[i] < zip[next])) {
                        next = i;
                    }
                }
            }
            if (next != -1) {
                visited[next] = true;
                ans += zip[next];
            }
        }
        
        cout << "Case #" << t << ": " << ans << endl;
    }
    
    return 0;
}
