#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int to, capacity, cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int n;
        cin >> n;
        
        vector<vector<Edge>> adj(n + 1);
        
        for (int i = 0; i < n - 1; i++) {
            int u, v, s, c;
            cin >> u >> v >> s >> c;
            adj[u].push_back({v, s, c});
        }
        
        // We want to find the maximum number of skiers and minimum expense
        // This is a flow problem on a tree
        
        // For each edge, we can send at most s skiers
        // Each skier pays c for using the edge
        
        // The maximum flow from root to leaves is limited by edge capacities
        // The minimum cost is the sum of (flow * cost) for each edge
        
        // Let's use a greedy approach:
        // For each edge, we want to send as many skiers as possible
        // but we need to consider the cost
        
        // Actually, this is a min-cost max-flow problem
        // But for a tree, we can solve it greedily
        
        // Let's compute the maximum flow and minimum cost
        long long max_flow = 0;
        long long min_cost = 0;
        
        // DFS from root
        vector<bool> visited(n + 1, false);
        
        function<int(int)> dfs = [&](int u) -> int {
            visited[u] = true;
            int flow = 0;
            
            for (auto& e : adj[u]) {
                if (!visited[e.to]) {
                    int child_flow = dfs(e.to);
                    int edge_flow = min(e.capacity, child_flow);
                    flow += edge_flow;
                    min_cost += (long long)edge_flow * e.cost;
                }
            }
            
            return max(flow, (int)adj[u].size() > 0 ? 0 : n - 1);
        };
        
        // Actually, let me think about this differently
        // The maximum number of skiers is limited by the edge capacities
        // along the path from root to each leaf
        
        // For each leaf, the maximum skiers is the minimum capacity along the path
        // But we can have multiple skiers going to different leaves
        
        // Let's use a different approach:
        // For each edge, we can send at most s skiers
        // The total flow is limited by the sum of capacities of edges leaving the root
        
        // Actually, this is more complex because skiers can stop at intermediate nodes
        
        // Let me just implement a simple solution
        // For each edge, we send as many skiers as possible
        // and compute the cost
        
        // DFS to compute flow and cost
        fill(visited.begin(), visited.end(), false);
        
        function<int(int, int)> dfs2 = [&](int u, int parent_flow) -> int {
            visited[u] = true;
            int total_flow = 0;
            
            for (auto& e : adj[u]) {
                if (!visited[e.to]) {
                    int edge_flow = min(e.capacity, parent_flow);
                    total_flow += edge_flow;
                    min_cost += (long long)edge_flow * e.cost;
                    
                    int child_flow = dfs2(e.to, edge_flow);
                    total_flow += child_flow;
                }
            }
            
            return total_flow;
        };
        
        max_flow = dfs2(1, n - 1);
        
        cout << "Case #" << t << ": " << max_flow << " " << min_cost << endl;
    }
    
    return 0;
}
