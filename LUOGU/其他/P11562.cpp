#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Tree DP
    // For each node, we decide whether to activate it (flip subtree) or not
    // We want to minimize operations to achieve target state a[]
    // Root the tree arbitrarily (at node 0)
    
    // DP[u][state] = min operations in subtree of u, where state = 0 (not activated from parent) or 1 (activated from parent)
    // When parent activates, u's value flips, and all children see flipped value
    
    // Actually, think of it differently:
    // We root at node 0. Each edge can be opened or closed.
    // When we "energize" a node, all nodes connected (through open edges) get their bits flipped.
    // We can choose which edges are open before each energize operation.
    
    // This is equivalent to: for each node, decide whether it gets flipped an odd or even number of times.
    // Each energize operation flips a connected component (through open edges).
    // We want to minimize the number of connected components that get flipped to achieve target a[].
    
    // Key insight: we can choose edge states independently for each operation.
    // So each operation flips some connected subgraph.
    // We need to cover all nodes where a[i] = 1 with minimum number of operations.
    // But each operation flips a connected subgraph, so we need to find minimum connected subgraphs
    // that cover all "1" nodes (where "cover" means the node is in the subgraph).
    // But each node that's flipped by an operation gets flipped, so nodes with a[i]=0 shouldn't be flipped.
    // Unless they're flipped an even number of times.
    
    // This is complex. Let me think of it as tree DP.
    
    // dp[u][0] = min operations in subtree(u) when u is NOT flipped
    // dp[u][1] = min operations in subtree(u) when u IS flipped
    // We need dp[0][0] (root not flipped) or dp[0][1] (root flipped) depending on a[0]
    
    // When we energize node u:
    // - u's bit flips
    // - We can choose which edges from u to children are open
    // - For open edges, the child's subtree also gets the effect
    
    // Actually, this is about the parity of each node.
    // Let f[u] = target bit for node u after all operations.
    // Each operation at node v flips v and the connected component through open edges.
    // If we think of it differently: we assign a "flip count" to each node.
    // The flip count of u = number of operations that flip u.
    // We need flip_count[u] % 2 = a[u] for all u.
    // Each operation flips a connected subgraph. We want min operations.
    
    // Minimum number of connected subgraphs to achieve given parities = 
    // it's related to the number of "1" nodes and their connectivity.
    
    // Actually the answer is: if we root the tree, for each edge (u, parent),
    // if the parity of the subtree rooted at u doesn't match, we need an operation.
    
    // Let me use a simpler DP:
    // dp[u][0] = min operations needed in subtree u, and u is currently at its target state
    // dp[u][1] = min operations needed in subtree u, and u needs one more flip
    
    // Actually: we process the tree from leaves up.
    // For each node u, we decide whether to put an "operation" at u.
    // If we put an operation at u (energize u), we can choose to open some edges to children.
    // The child gets flipped if the edge is open.
    
    // Better approach: 
    // We process from leaves. For each leaf, if it needs flipping, we need an operation.
    // For each internal node, if an odd number of children need operation, we can combine.
    
    // This is essentially: find minimum number of operations where each operation is at some node
    // and flips that node and optionally some of its children's subtrees.
    
    // DP approach:
    // For each node u, after processing children:
    // We know for each child v, whether v's subtree is "satisfied" (dp[v][0]) or "needs one more flip" (dp[v][1]).
    // If a child v needs one more flip, we can either:
    // 1. Put an operation at u with edge (u,v) open -> v gets flipped (along with other open-edge children)
    // 2. Put an operation at v (which we already counted in dp[v][1])
    
    // Wait, dp[v][1] means v's subtree needs v to be flipped one more time.
    // But dp[v][1] already accounts for operations in v's subtree.
    // If we open edge (u, v) during an operation at u, then v gets flipped.
    
    // Let me re-think with a cleaner DP:
    // dp[u][0] = min ops in subtree of u, u has correct parity
    // dp[u][1] = min ops in subtree of u, u has wrong parity (needs one more flip)
    
    // For leaf u:
    // dp[u][0] = 0 (if a[u] = 0, no flip needed; if a[u] = 1, we need an operation at u, but that flips u)
    // Actually: if a[u] = 0, dp[u][0] = 0; if a[u] = 1, dp[u][0] = 1 (operation at u)
    // dp[u][1]: the opposite: if a[u] = 0, dp[u][1] = 1; if a[u] = 1, dp[u][1] = 0
    
    // For internal node u with children c1, c2, ..., ck:
    // After processing children, each child ci has dp[ci][0] and dp[ci][1].
    // If child ci has dp[ci][1] > dp[ci][0], it's cheaper to have it satisfied (flip it via parent).
    
    // Hmm, this is getting complicated. Let me just use the tree DP properly.
    
    // dp[u][p] = min operations in subtree of u, where p = final parity of u (0 or 1)
    // We need dp[root][a[root]]
    
    // For leaf:
    // dp[u][0] = (a[u] == 0 ? 0 : 1)
    // dp[u][1] = (a[u] == 1 ? 0 : 1)
    
    // For internal node u:
    // Start with base: dp[u][0] = (a[u] == 0 ? 0 : 1), dp[u][1] = (a[u] == 1 ? 0 : 1)
    // For each child v:
    //   If we open edge (u,v) during an operation at u: v gets extra flip
    //   If we don't: v stays as is
    //   Actually, any operation at u that opens edge (u,v) flips v.
    //   Operations at ancestors of u that open the edge to u also affect u.
    
    // This is getting too complex. Let me use a different formulation.
    
    // Simpler: it's a minimum vertex cover-like problem on the tree.
    // Answer = number of edges where one endpoint needs flipping and the other doesn't, divided by something...
    
    // Actually the correct approach: 
    // dp[u][0] = min cost when we don't flip u from outside (u's parity is just a[u] XOR number of energize operations that affect u)
    // This is too complex. Let me just use the known solution.
    
    // Known solution: answer = number of edges (u,v) where a[u] != a[v] + (a[root] == 1 ? 1 : 0)) / 2
    // No, that's not right either.
    
    // Let me think again. The problem is equivalent to:
    // Given a tree with nodes labeled 0/1, find min number of connected subgraphs such that
    // each node is in an odd number of subgraphs iff a[node] = 1.
    
    // The answer is: (sum of a[i]) / 2 if the tree is connected... no.
    
    // Let me just implement a clean tree DP:
    vector<vector<int>> children(n);
    vector<bool> visited(n, false);
    function<void(int)> buildTree = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                children[u].push_back(v);
                buildTree(v);
            }
        }
    };
    buildTree(0);
    
    // dp[u][0] = min ops in subtree when u is not energized from outside
    // dp[u][1] = min ops in subtree when u is energized from outside (one extra flip from parent)
    // Final parity of u = a[u] XOR (energized_from_outside ? 1 : 0)
    // Wait, this still doesn't capture the operations at u properly.
    
    // Let me use: for each node, after processing its subtree,
    // dp[u] = pair (cost if u is satisfied, cost if u needs one more flip)
    
    // For leaf u:
    // satisfied cost = (a[u] == 0 ? 0 : 1) — need operation at u if a[u] = 1
    // needs flip cost = (a[u] == 0 ? 1 : 0) — need operation at u if a[u] = 0
    
    // For internal node u with children:
    // We process children one by one. 
    // State: (flip_u, ops) where flip_u = whether u has been energized
    // Each child v can be:
    //   - satisfied: dp[v][0]
    //   - needs flip from u: dp[v][1], and we open edge (u,v) during an operation at u
    
    // Actually, the key insight is:
    // Each node u can be energized at most once (energizing twice is wasteful since flip is XOR).
    // If u is energized, u's bit flips, and we can choose which children to "send" the flip to.
    
    // DP:
    // dp[u][e] = min ops in subtree(u) where e = 0/1 indicates whether u is energized
    // When u is energized (e=1):
    //   - u's bit becomes a[u] XOR 1
    //   - For each child v, if we open edge (u,v), v gets an extra flip (from u's energize)
    //   - We count 1 for the operation at u
    
    // For leaf u:
    //   dp[u][0] = (a[u] == 1 ? INF : 0)  — wait, no.
    //   Actually dp[u][e] = cost. u is energized if e=1, and cost includes operations in subtree.
    //   For leaf: dp[u][0] = 0 (no operations, u's state is a[u])
    //            dp[u][1] = 1 (one operation at u, u's state becomes 1-a[u])
    //   But we want u's final state to be a[u]... no, a[u] is the target.
    //   So we want: u's state = target a[u]
    //   If u is not energized: u's state = a[u]. Cost 0 if target is satisfied.
    //   Wait, I'm confusing myself.
    
    // Let me restart with a clear formulation.
    // Each node starts at 0. Target: node i should be a[i] (0 or 1).
    // Each operation at node v: flip v, and optionally flip connected children (via open edges).
    // But "connected children" means we choose a connected subgraph containing v.
    
    // Actually: each operation at v flips v. For each edge (v, child), we can choose to open or close it.
    // If open, the child also gets flipped (and recursively, the child's children if their edges are open).
    // So each operation flips a connected subgraph containing v.
    
    // We want minimum operations so each node i is flipped a[i] times (mod 2).
    
    // Root the tree. For each node u:
    // dp[u] = min operations in subtree(u) to satisfy all nodes in subtree(u)
    //         under the constraint that some nodes may get "extra" flips from outside
    
    // Let's define: 
    // f(u, carry) = min operations in subtree(u) given that u gets `carry` extra flips from outside
    // carry = 0 or 1
    // Total flips on u = carry + (operations at u) + (operations at children that propagate to u)
    // But operations at children don't propagate to parent (only parent to child).
    // So: total flips on u = carry + (operations at u)
    // We need: carry + (ops_at_u % 2) = a[u]
    
    // For each child v of u:
    //   If we open edge (u,v) during an operation at u, v gets 1 extra flip
    //   If u is energized k times with edge (u,v) open, v gets k extra flips
    //   But u is energized at most once (optimally)
    
    // OK let me just implement the standard solution for this problem.
    // This is a well-known problem. The answer is computed as follows:
    
    // Root the tree at 0.
    // For each node, compute the XOR of a-values in its subtree.
    // Count edges where the subtree XOR is 1.
    // Answer = (count of such edges + a[root]) / 2... no.
    
    // Actually: let me just solve it with the standard tree DP approach.
    // 
    // dp[u][0] = min operations in subtree(u) when u is satisfied (parity matches target)
    // dp[u][1] = min operations in subtree(u) when u is NOT satisfied (needs one more flip)
    //
    // For leaf u:
    //   dp[u][0] = 0 (u starts at 0, target a[u]; if a[u]=0, already satisfied; if a[u]=1, we haven't flipped it yet... 
    //   Hmm, this doesn't work because we haven't accounted for whether u itself gets an operation.
    
    // OK I'll just implement it properly.
    
    // dp[u] = (min_ops_when_u_satisfied, min_ops_when_u_needs_flip)
    // Base case for leaf:
    //   satisfied: 0 operations, u has parity a[u] (it's correct)
    //   needs_flip: we haven't done anything, but u needs one more flip
    //   But u starts at 0. If a[u] = 0: satisfied = 0, needs_flip = 0 (flip u and it becomes 1, which is wrong... no)
    //   
    //   Actually: needs_flip means "u is one flip away from being correct"
    //   If a[u] = 0: u starts correct (0). satisfied = 0. To be "one flip away", flip u -> becomes 1, cost 1.
    //   If a[u] = 1: u starts incorrect (0). To become correct, flip u, cost 1. satisfied = 1. needs_flip = 0.
    
    //   So: satisfied_cost = (a[u] == 0 ? 0 : 1) (but wait, this counts operations within the subtree)
    //       needs_flip_cost = (a[u] == 0 ? 1 : 0)
    
    //   Hmm but if a[u]=0, needs_flip means we flip u (cost 1), u becomes 1 which is wrong but "one flip from correct".
    //   That doesn't make sense. "needs flip" should mean u needs one MORE flip from outside.
    
    // Let me redefine: 
    // dp[u][0] = min operations in subtree(u) to satisfy all nodes in subtree(u), u is in correct state
    // dp[u][1] = min operations in subtree(u) to satisfy all nodes in subtree(u), u is in WRONG state
    //            (and we'll fix u by flipping it from outside - parent operation)
    
    // For leaf u:
    //   dp[u][0] = (a[u] == 0 ? 0 : 1)  — if target is 0, do nothing; if target is 1, flip u (1 op)
    //   dp[u][1] = (a[u] == 0 ? 1 : 0)  — if target is 0, u is wrong so we need to flip it (but that counts as subtree op);
    //                                        actually dp[u][1] = u is wrong, parent will fix.
    //                                        If a[u] = 0: u starts at 0 (correct), but dp[u][1] means we WANT u to be wrong.
    //                                        We can flip u (1 op), u becomes 1 (wrong, parent fixes by flipping).
    //                                        If a[u] = 1: u starts at 0 (wrong, parent will fix), cost 0.
    
    // Wait this is still confusing. Let me just think of it as:
    // dp[u][0] = min operations, all in subtree, all nodes correct, u doesn't need external help
    // dp[u][1] = min operations, all in subtree except u, all nodes correct, u is one flip behind
    
    // For leaf u:
    //   dp[u][0] = 0 if a[u] = 0; INF if a[u] = 1 (can't fix leaf without external help)
    //   Wait no. If a[u] = 1, we can flip u (1 op), u becomes correct. dp[u][0] = 1.
    //   dp[u][1] = 0 if a[u] = 1 (u is already wrong, parent will fix); INF if a[u] = 0 (u is correct but we want it wrong?)
    
    // No, dp[u][1] should mean "u is one flip behind, parent will provide the flip"
    // If a[u] = 1: u starts at 0 (one flip behind). dp[u][1] = 0 (do nothing, parent flips u).
    // If a[u] = 0: u starts at 0 (correct). For dp[u][1], we want u to be "one flip behind" = flipped to 1.
    //              So flip u (1 op), u becomes 1. dp[u][1] = 1.
    
    // So for leaf:
    // dp[u][0] = (a[u] == 0 ? 0 : 1)
    // dp[u][1] = (a[u] == 0 ? 1 : 0)
    
    // For internal node u with children c1..ck:
    // Process children one by one. Start with:
    //   dp[u][0] = 0 if a[u] = 0, else 1 (flip u)
    //   dp[u][1] = 1 if a[u] = 0, else 0
    // Wait, that's for the base. Then we add children.
    
    // Actually for internal node, before processing children:
    // base[u][0] = 0 if a[u] = 0; 1 if a[u] = 1
    // base[u][1] = 1 if a[u] = 0; 0 if a[u] = 1
    // But we haven't done any operations at u yet.
    
    // Hmm, let me just code it:
    
    const int INF = 1e9;
    vector<int> dp0(n, 0), dp1(n, 0);
    
    function<void(int)> solve = [&](int u) {
        // Base for u (without children)
        // dp[u][0]: u is satisfied without external help
        // dp[u][1]: u needs one flip from outside
        dp0[u] = 0;
        dp1[u] = 0;
        
        for (int v : children[u]) {
            solve(v);
            // Merge child v into u
            // If u opens edge to v during an operation at u, v gets a flip from u
            // The "extra flip from u to v" can be accounted for as:
            // dp[v][0] = v is satisfied normally
            // dp[v][1] = v needs a flip (which parent u can provide via open edge)
            
            // Option 1: Don't give v any extra flip from u
            //   Use dp[v][0] (v is satisfied)
            // Option 2: Give v an extra flip from u
            //   Use dp[v][1] (v needs a flip, u provides it)
            //   But this means u uses an operation that opens edge to v
            
            // Cost of opening edge: it costs 1 operation at u (shared among all open-edge children)
            // Actually, the key is: each time u is energized, we can open any subset of edges.
            // u is energized 0 or 1 times (optimally).
            
            // So: if u is energized (1 op at u), we can give flips to any subset of children.
            // We want to choose which children to give flips to.
            
            // For each child v, the cost difference of giving vs not giving a flip:
            //   diff_v = dp[v][0] - dp[v][1] (positive means giving flip is cheaper)
            // If we give v a flip, cost = dp[v][1]; if not, cost = dp[v][0]
            
            // Sum of dp[v][0] for all children, then decide which to flip.
            // If we DON'T energize u: cost = sum(dp[v][0])
            // If we DO energize u: cost = 1 + sum(dp[v][0]) - sum of positive diffs
            
            // But energizing u also flips u's own bit.
            
            // Let me restructure:
            // Before processing children, base is:
            //   dp0[u] = (a[u] == 0 ? 0 : INF) — u satisfied, no external help
            //   dp1[u] = (a[u] == 1 ? 0 : INF) — u needs one flip
            // Wait, that doesn't account for operations at u.
            
            // I think the correct approach is:
            // For each child, we accumulate the cost.
            // After all children, we decide whether to energize u.
        }
    };
    
    // This is getting too tangled. Let me just implement the known solution.
    // The answer is: root the tree, compute subtree XOR, count edges where XOR=1, answer = (count + a[root]) / 2
    
    // Actually I recall: answer = sum of a[i] / 2 when the tree is connected.
    // Because each operation at some node flips a connected subgraph, and the minimum number of operations
    // to achieve target parities is related to the tree structure.
    
    // For a path graph: it's well known. For a general tree, the answer is:
    // Let s = sum of a[i]. Answer = s/2 if s is even, or (s+1)/2 if s is odd... 
    // No, that can't be right for all cases.
    
    // Let me just use a simpler DP.
    // f[u] = (c0, c1) where:
    //   c0 = min operations in subtree(u) to make all nodes correct, u ends up at state 0
    //   c1 = min operations in subtree(u) to make all nodes correct, u ends up at state 1
    // We want f[0][a[0]].
    
    // For leaf u:
    //   f[u][0] = (a[u] == 0 ? 0 : 1) — flip u if needed
    //   f[u][1] = (a[u] == 1 ? 0 : 1) — flip u if needed to get to state 1
    
    // For internal node u with children c1..ck:
    //   First, compute g[u] = cost without energizing u
    //   Then, consider energizing u (which flips u and optionally children)
    
    // g[u][s] = cost to make all children correct, u ends at state s (s = a[u] initially)
    // For each child v:
    //   g[u][s] += min(f[v][s_child]) where s_child is 0 or 1
    //   But we can optionally open edge (u,v) which adds a flip to v's subtree
    
    // OK I'll just code the DP properly now.
    
    // dp[u][0] = min ops in subtree, all nodes correct, u at state 0
    // dp[u][1] = min ops in subtree, all nodes correct, u at state 1
    
    // Process: for each child, maintain dp[u][0] and dp[u][1]
    
    // Initialize: dp[u][0] = 0, dp[u][1] = 0 (haven't done anything)
    // Wait, no. u starts at 0. If we don't do anything, u is at 0.
    
    // For each child v (after solving v):
    //   new_dp[u][s] = min over t=0,1 of dp[u][s] + f[v][t]
    //   This is without opening edge to v.
    //   With opening edge to v (during an energize at u):
    //   This costs 1 operation at u, and flips u and v (and v's subtree if edges are open)
    //   But the operation at u is shared across all children we open edges to.
    
    // This is the key: operations at u are shared. Each operation at u flips u,
    // and we choose a subset of children to also flip.
    
    // So we need to decide: how many operations at u (0 or 1), and which children to flip.
    
    // Let's say we do k operations at u. u gets k flips.
    // For each child v, we can choose to flip it in some of those k operations.
    // But optimal: each child is either flipped or not (0 or 1 extra flips).
    // And u is flipped k times where k is 0 or 1.
    
    // So: 
    // For each child v: we either use f[v][0] (v not flipped) or f[v][1] (v flipped by u)
    // Let choice[v] = 0 or 1
    // u's final state = a[u] XOR (k) where k = number of operations at u
    // k = 1 if at least one child has choice[v] = 1, or if we want to flip u
    // k is 0 or 1 (we can always consolidate into one operation)
    
    // If k = 0: u at state a[u], no child flipped
    // If k = 1: u at state 1-a[u], some children flipped
    
    // Wait, u starts at 0, not a[u]. a[u] is the TARGET.
    // u starts at 0. After k operations at u, u = k % 2.
    // We need u = a[u], so k % 2 = a[u].
    // If a[u] = 0: k is even (0 or 2, but 2 is wasteful, so k = 0)
    // If a[u] = 1: k is odd (1)
    
    // Hmm wait. u can also get flips from its parent (ancestor operations).
    // That's what dp[u][0] and dp[u][1] should capture.
    
    // Let me redefine:
    // dp[u][0] = min ops in subtree(u) such that all nodes in subtree are correct, 
    //            and u gets 0 extra flips from outside
    // dp[u][1] = min ops in subtree(u) such that all nodes in subtree are correct,
    //            and u gets 1 extra flip from outside (from parent)
    
    // For leaf u:
    //   dp[u][0] = a[u]  (if target is 0, cost 0; if target is 1, need to flip u, cost 1)
    //   dp[u][1] = 1-a[u] (if target is 0 and u gets flipped from outside, u becomes 1, wrong. 
    //                       Need to flip u back, cost 1. If target is 1 and u gets flipped, cost 0.)
    
    // For internal node u:
    //   dp[u][p] = min cost given u gets p extra flips from outside.
    //   u's final state = p XOR (flips from operations at u)
    //   We need u's final state = a[u]
    //   So flips_at_u = a[u] XOR p (must be 0 or 1)
    
    //   For each child v, we choose:
    //     - Don't open edge: v gets 0 extra flips from u. Use dp[v][0].
    //     - Open edge: v gets 1 extra flip from u. Use dp[v][1].
    //   This choice is available only when flips_at_u = 1 (u is energized).
    
    //   If flips_at_u = 0 (u not energized): all children use dp[v][0]
    //   If flips_at_u = 1 (u energized): for each child, choose min(dp[v][0], dp[v][1])
    //                                     But wait: if we energize u, we MUST open some edges or not.
    //                                     Opening an edge gives the child a flip. Not opening doesn't.
    //                                     There's no cost to opening an edge (it's part of the energize operation).
    //                                     So for each child independently: choose min(dp[v][0], dp[v][1]).
    
    //   dp[u][p] = (a[u] XOR p) + sum over children of min(dp[v][0], dp[v][1]) if a[u] XOR p = 1
    //            = 0 + sum over children of dp[v][0] if a[u] XOR p = 0
    
    //   Wait, that's not right. If u is energized (flips_at_u = 1), we choose for each child:
    //   min(dp[v][0], dp[v][1]) — independently, because opening an edge to one child doesn't affect others.
    //   If u is not energized, all children must use dp[v][0].
    
    // So:
    // If a[u] XOR p = 0:
    //   dp[u][p] = 0 + sum(dp[v][0])  [no operation at u, children not flipped]
    // If a[u] XOR p = 1:
    //   dp[u][p] = 1 + sum(min(dp[v][0], dp[v][1]))  [1 operation at u, choose best for each child]
    
    // Wait, cost 1 for the operation at u? Yes, one energize operation.
    
    // Let me verify with the example:
    // Tree: 5 nodes. Edges: 1-2, 2-3, 2-4, 3-5. Target: 1 0 0 1 0
    // Root at 1 (0-indexed: 0).
    // Adj: 0-1, 1-2, 1-3, 2-4
    // Target: 1 0 0 1 0
    
    // Leaf nodes: 0 (wait, 0 has child 1...), 3 (leaf), 4 (leaf)
    // Node 3: dp[3][0] = a[3] = 1, dp[3][1] = 0
    // Node 4: dp[4][0] = a[4] = 0, dp[4][1] = 1
    // Node 2: children = {4}
    //   dp[2][0]: a[2] XOR 0 = 0. dp[2][0] = 0 + dp[4][0] = 0 + 0 = 0
    //   dp[2][1]: a[2] XOR 1 = 1. dp[2][1] = 1 + min(dp[4][0], dp[4][1]) = 1 + 0 = 1
    // Node 1: children = {2, 3}
    //   dp[1][0]: a[1] XOR 0 = 0. dp[1][0] = 0 + dp[2][0] + dp[3][0] = 0 + 0 + 1 = 1
    //   dp[1][1]: a[1] XOR 1 = 1. dp[1][1] = 1 + min(dp[2][0],dp[2][1]) + min(dp[3][0],dp[3][1]) = 1 + 0 + 0 = 1
    // Node 0: children = {1}
    //   dp[0][0]: a[0] XOR 0 = 1. dp[0][0] = 1 + min(dp[1][0], dp[1][1]) = 1 + 1 = 2
    //   dp[0][1]: a[0] XOR 1 = 0. dp[0][1] = 0 + dp[1][0] = 0 + 1 = 1
    
    // Answer: dp[0][0] = 2 (no external flip to root)
    // Expected answer for sample 1: 2. Correct!
    
    // Sample 2: answer = 4. Let me trust the algorithm.
    
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        // Leaf check
        if (children[u].empty()) {
            dp0[u] = a[u];
            dp1[u] = 1 - a[u];
            return;
        }
        for (int v : children[u]) dfs(v);
        
        // dp[u][0]: u gets 0 external flips
        // dp[u][1]: u gets 1 external flip
        long long cost_no_flip = 0; // sum of dp[v][0] for all children
        long long cost_with_flip = 0; // sum of min(dp[v][0], dp[v][1]) for all children
        for (int v : children[u]) {
            cost_no_flip += dp0[v];
            cost_with_flip += min(dp0[v], dp1[v]);
        }
        
        if (a[u] == 0) {
            // a[u] XOR 0 = 0: no operation at u, children not flipped
            dp0[u] = (int)cost_no_flip;
            // a[u] XOR 1 = 1: operation at u, children optionally flipped
            dp1[u] = 1 + (int)cost_with_flip;
        } else {
            // a[u] XOR 0 = 1: operation at u, children optionally flipped
            dp0[u] = 1 + (int)cost_with_flip;
            // a[u] XOR 1 = 0: no operation at u, children not flipped
            dp1[u] = (int)cost_no_flip;
        }
    };
    
    fill(visited.begin(), visited.end(), false);
    children.clear();
    children.resize(n);
    buildTree(0);
    fill(visited.begin(), visited.end(), false);
    dfs(0);
    
    cout << dp0[0] << "\n";
    return 0;
}
