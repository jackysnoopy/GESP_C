#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> k(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }
    
    vector<vector<int>> graph(n + 1);
    vector<int> indegree(n + 1, 0);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        indegree[b]++;
    }
    
    // Part 1: Find a valid topological order
    // Use min-heap to get lexicographically smallest order
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }
    
    vector<int> order;
    
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        order.push_back(u);
        
        for (int v : graph[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                pq.push(v);
            }
        }
    }
    
    // Output valid order
    for (int i = 0; i < n; i++) {
        cout << order[i] << (i == n - 1 ? "\n" : " ");
    }
    
    // Part 2: Find minimum possible position for each node
    // For each node, its minimum position is max(k[i], number of predecessors + 1)
    vector<int> min_pos(n + 1, 1);
    
    // Process in reverse topological order
    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        min_pos[u] = max(min_pos[u], k[u]);
        
        // Propagate to predecessors
        for (int v : graph[u]) {
            min_pos[v] = max(min_pos[v], min_pos[u] + 1);
        }
    }
    
    // Output minimum positions
    for (int i = 1; i <= n; i++) {
        cout << min_pos[i] << (i == n ? "\n" : " ");
    }
    
    return 0;
}
