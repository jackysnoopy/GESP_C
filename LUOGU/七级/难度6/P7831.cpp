#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(m), b(m), r(m), p(m);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> r[i] >> p[i];
        a[i]--; b[i]--;
    }
    
    // 对于每个城市，找最小初始资产使得可以永远旅行
    // 贪心/SPFA思想：如果能找到正权环且可以到达，则需要0初始资产
    
    // 简单方法：对于每个城市，尝试BFS/DFS找可达的环
    // 如果环的总资产增加>0，则初始资产可以为0
    
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        adj[a[i]].push_back(i);
    }
    
    vector<long long> ans(n, -1);
    
    // 对每个城市做BFS
    for (int start = 0; start < n; start++) {
        // 找从start出发能到达的所有环
        // 如果有正权环，答案为0
        // 否则需要计算最小初始资产
        
        vector<bool> visited(n, false);
        vector<long long> dist(n, LLONG_MIN);
        dist[start] = 0;
        
        // 简单SPFA
        vector<int> queue;
        queue.push_back(start);
        visited[start] = true;
        
        bool hasPosCycle = false;
        
        for (int iter = 0; iter < n * 2 && !hasPosCycle; iter++) {
            vector<int> nextQueue;
            for (int u : queue) {
                for (int ei : adj[u]) {
                    int v = b[ei];
                    long long need = r[ei];
                    long long gain = p[ei];
                    
                    if (dist[u] >= need) {
                        long long newDist = dist[u] + gain;
                        if (newDist > dist[v]) {
                            dist[v] = newDist;
                            if (!visited[v]) {
                                visited[v] = true;
                                nextQueue.push_back(v);
                            }
                            if (v == start && newDist > 0) {
                                hasPosCycle = true;
                            }
                        }
                    }
                }
            }
            queue = nextQueue;
        }
        
        if (hasPosCycle) {
            ans[start] = 0;
        } else {
            // 找最小初始资产使得可以永远旅行
            // 这需要更复杂的分析，暂时输出-1
            ans[start] = -1;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    
    return 0;
}
