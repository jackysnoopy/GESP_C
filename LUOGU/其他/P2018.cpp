#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// P2018: 消息传递
// Tree DP: find minimum time to spread message from root to all nodes.
// And find all possible starting nodes.
// Tree DP: for each node, compute the time to spread from it.
// Key: the answer is related to the tree diameter.

int n;
vector<vector<int>> adj;
vector<int> parent;
vector<int> order;
int ans_time;

// DP: dp[u] = max distance from u to any leaf in its subtree
// The minimum time to spread from u = max over children of (dp[v]+1, ...)
// Actually this is the problem where you tell one person, and at each time step,
// each informed person tells one direct superior or subordinate.
// This is equivalent to: the minimum time is the tree diameter / 2 (ceiling).

void dfs1(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v != p) dfs1(v, u);
    }
}

// Find all nodes whose eccentricity equals the answer
// The answer is ceil(diameter/2).
// A node is optimal if its maximum distance to any other node = answer.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    adj.resize(n + 1);
    parent.resize(n + 1);
    
    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    
    if (n == 1) {
        cout << "0\n1\n";
        return 0;
    }
    
    // BFS from node 1 to find farthest
    vector<int> dist(n + 1, -1);
    dist[1] = 0;
    vector<int> q;
    q.push_back(1);
    int far1 = 1;
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        far1 = u;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    
    // BFS from far1
    fill(dist.begin(), dist.end(), -1);
    dist[far1] = 0;
    q.clear();
    q.push_back(far1);
    int far2 = far1;
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        far2 = u;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push_back(v);
            }
        }
    }
    
    int diameter = dist[far2];
    int answer = (diameter + 1) / 2;
    cout << answer << "\n";
    
    // Find all nodes with eccentricity = answer
    // eccentricity = max distance to any node
    // For the center of the tree, eccentricity = ceil(diameter/2)
    // Need to find all such nodes.
    
    // BFS from far2 to get distances
    vector<int> dist2(n + 1, -1);
    dist2[far2] = 0;
    q.clear();
    q.push_back(far2);
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        for (int v : adj[u]) {
            if (dist2[v] == -1) {
                dist2[v] = dist2[u] + 1;
                q.push_back(v);
            }
        }
    }
    
    // dist from far1 and dist2 from far2
    // eccentricity of node u = max(dist[u], dist2[u])
    vector<int> result;
    for (int u = 1; u <= n; u++) {
        if (max(dist[u], dist2[u]) == answer) {
            result.push_back(u);
        }
    }
    
    sort(result.begin(), result.end());
    for (int i = 0; i < (int)result.size(); i++) {
        cout << result[i] << (i + 1 < (int)result.size() ? " " : "\n");
    }
    return 0;
}
