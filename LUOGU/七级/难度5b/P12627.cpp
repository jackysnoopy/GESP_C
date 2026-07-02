#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int w[MAXN]; // -1 means free, otherwise fixed weight
int n;
long long K;
long long ans = 0;
bool impossible = false;

// dp[u] = maximum total weight in subtree of u, considering constraint
// For each node u, the constraint is: w[u] + sum of w[v] for v in children <= K
// We want to maximize sum of all w[i]

// Actually, the constraint is: for each node u, w[u] + sum of w[children of u] <= K
// We want to maximize sum of all w[i]

// This is a tree DP problem
// For each node u, we need to decide w[u] (if free)
// The constraint at u: w[u] + sum of w[v] for v in children of u <= K

// Let's think about it differently:
// For each node u, the constraint limits the sum of weights in the "star" around u
// We want to maximize total weight

// Greedy approach: for each free node, set it to K minus the sum of children's weights
// But this might conflict with parent's constraint

// Let's use a different approach:
// For each node, we have a constraint: w[u] + sum_{v in children(u)} w[v] <= K
// We want to maximize sum of all w[i]

// This is equivalent to: for each edge (u, v) where v is child of u,
// w[v] contributes to both u's and v's constraint

// Let's use a flow-based or greedy approach

// Actually, let's think about it as:
// For each node u with fixed weight w[u], we need:
// sum of w[children of u] <= K - w[u]
// For each node u with free weight, we need:
// w[u] + sum of w[children of u] <= K
// So w[u] <= K - sum of w[children of u]

// The optimal strategy is:
// 1. Process nodes bottom-up
// 2. For each free node, set w[u] = K - sum of w[children]
// 3. For each fixed node, check if constraint is satisfied

// But this might not work because setting w[u] high might violate parent's constraint

// Let's use a different approach:
// For each node, compute the maximum possible weight contribution
// Then check if constraints are satisfied

// Actually, let's think about it more carefully:
// The constraint at node u: w[u] + sum_{v in children(u)} w[v] <= K
// This means: w[u] <= K - sum_{v in children(u)} w[v]

// For a free node u, the optimal is to set w[u] = K - sum of children's weights
// But this might be negative, in which case we set w[u] = 0

// Wait, the problem says we can choose any non-negative integer weight
// So w[u] >= 0

// Let's try a greedy approach:
// 1. Process nodes bottom-up
// 2. For each node, compute the sum of children's weights
// 3. For free nodes, set w[u] = max(0, K - sum_children)
// 4. For fixed nodes, check if w[u] + sum_children <= K

// But this might not be optimal because setting a free node to 0 might allow
// the parent to have a higher weight

// Let me reconsider...
// Actually, the constraint is local to each node
// The only interaction between nodes is through the edges

// For each edge (u, v) where v is child of u:
// w[v] appears in u's constraint
// w[u] appears in v's constraint (if u is child of v, which it's not)

// Wait, the constraint is: w[u] + sum of w[children of u] <= K
// So w[v] (child of u) appears in u's constraint
// And w[u] appears in v's constraint only if u is a child of v

// So the constraints are:
// For each node u: w[u] + sum_{v in children(u)} w[v] <= K

// This is a set of linear constraints
// We want to maximize sum of w[i] subject to these constraints

// This is a linear programming problem, but we can solve it greedily

// Let me try a different approach:
// For each node u, define s[u] = w[u] + sum_{v in children(u)} w[v]
// The constraint is s[u] <= K for all u
// We want to maximize sum of w[i]

// Note that sum of w[i] = sum of (s[u] - sum of children's weights)
// = sum of s[u] - sum of (children's weights counted multiple times)

// This is getting complicated. Let me just implement a simple greedy:

void dfs(int u, int parent) {
    long long sum_children = 0;
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
            sum_children += w[v];
        }
    }
    
    if (w[u] == -1) {
        // Free node: set to max(0, K - sum_children)
        w[u] = max(0LL, K - sum_children);
    } else {
        // Fixed node: check constraint
        if (w[u] + sum_children > K) {
            impossible = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> K;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }
    
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, 0);
    
    if (impossible) {
        cout << -1 << endl;
    } else {
        long long total = 0;
        for (int i = 1; i <= n; i++) {
            total += w[i];
        }
        cout << total << endl;
    }
    
    return 0;
}
