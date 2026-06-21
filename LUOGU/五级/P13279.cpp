// P13279: 生长的树
// T1 grows as a k-ary tree. At each moment:
//   1. All nodes with < k children get filled to exactly k children.
//   2. We can prune any non-root subtrees.
//
// T2 is the target: n nodes, root=1, edges given.
// Goal: make T1 match T2 (same nodes 1..n, same parent structure).
// Find: earliest moment p, and minimum operations q.
//
// Key insight:
// At moment t, the k-ary tree has depth t.
// Each node at depth < t has exactly k children.
// We assign node IDs 1..n to positions in the tree.
// After assignment, some "extra" nodes exist that need to be pruned.
//
// The constraint: for each node i (2..n), parent_T1(i) = parent_T2(i).
// In the k-ary tree at moment t, parent(i) must have room for i as a child.
// Each parent can have at most k children.
//
// The minimum moment p: the smallest t such that T2 can be embedded.
// This is determined by the "width" of T2 at each depth.
// At depth d in T2, let w(d) = number of nodes. We need w(d) <= k^d for all d.
// Wait, that's for a full k-ary tree. But T2 is not necessarily a k-ary tree.
//
// Actually, the constraint is simpler: each node in T2 has at most k children (given).
// So the embedding is always possible as long as the depth of T2 <= t.
//
// But wait, at moment t, the tree has depth t. After pruning, we can have any structure
// with depth <= t and each node having at most k children.
//
// So p = depth of T2 (the height of T2).
//
// But the sample says: n=6, k=3, T2 edges: 1-2, 1-5, 2-3, 2-4, 5-6.
// Depth of T2: root=1, depth 1: {2,5}, depth 2: {3,4,6}. So depth=2.
// Answer: p=2, q=4.
//
// At moment 2: T1 has root (1) with k=3 children, each with k=3 children.
// Total nodes: 1 + 3 + 9 = 13. We need 6 nodes (1..6).
// We assign: 1=root, 2,5=depth-1 children of 1, 3,4,6=depth-2 children.
// Extra nodes to prune: 13 - 6 = 7. But q=4, not 7.
//
// The pruning is by subtree: we prune entire subtrees, not individual nodes.
// So we need to find the minimum number of subtree prunings.
//
// At moment 2:
// Root has 3 children. We assign 2 of them as nodes 2 and 5.
// The 3rd child is "extra" and can be pruned (1 operation).
// Node 2 has 3 children. We assign 2 of them as nodes 3 and 4.
// The 3rd child is extra (prune: 1 operation).
// Node 5 has 3 children. We assign 1 of them as node 6.
// The other 2 are extra (prune: 1 operation, since they're under the same parent).
// Wait, each extra child is a separate subtree. So 2 operations for node 5's extras.
//
// Total operations: 1 (root's extra) + 1 (node 2's extra) + 2 (node 5's extras) = 4. ✓
//
// So the formula for q:
// For each node i in T2 with c_i children:
//   extra children = k - c_i (at the moment when i is created).
//   But we can prune the entire group of extra children as separate subtrees.
//   Each extra child is a separate subtree root, so each needs 1 operation.
//   Extra operations for node i = k - c_i.
//
// Wait, that gives: root has 3-2=1 extra, node 2 has 3-2=1 extra, node 5 has 3-1=2 extras.
// Total: 1+1+2=4. ✓
//
// But this is only correct if we prune at the right moment. If we prune earlier,
// some extra children might not exist yet.
//
// Actually, the pruning happens AFTER the tree grows. So at moment p, all nodes
// at depth p have been created. We then prune the extra subtrees.
//
// For each node i at depth d < p:
//   At moment d+1, node i gets k children.
//   c_i of them are used (for T2 children).
//   k - c_i are extra and need to be pruned.
//
// But if we prune at moment p, the extra children at depth d+1 might have grown
// into full subtrees of depth p-d-1. We still only need 1 operation per extra child
// (prune the entire subtree).
//
// So q = sum over all nodes i of (k - c_i), where c_i is the number of children of i in T2.
// = sum(k) - sum(c_i) = n_internal * k - (n - 1).
// Where n_internal is the number of non-leaf nodes.
//
// Wait, sum(c_i) = n - 1 (total edges in tree).
// And the sum is over all nodes, including leaves (which have c_i = 0).
// So q = n * k - (n - 1) - (number of leaves * k - 0)... hmm, let me recalculate.
//
// q = sum_{i=1}^{n} (k - c_i) = n*k - sum(c_i) = n*k - (n-1).
// For the sample: 6*3 - 5 = 18 - 5 = 13. But expected is 4.
//
// That's way off. The issue is that we don't need to prune extra children of LEAVES.
// Leaves don't have children, so they don't create extra subtrees.
//
// Wait, at moment p, ALL nodes at depth < p have k children. Including leaves of T2.
// But we can choose NOT to assign children to leaf nodes of T2.
// Actually, the tree grows automatically: at each moment, ALL nodes with < k children
// get filled to k children. We can't prevent this.
//
// But we CAN prune subtrees. So at moment 1, we can prune the extra children of leaves.
// This prevents them from growing further.
//
// Hmm, but the pruning happens AFTER the growth at each moment. So:
// Moment 1: root gets k children. We prune extras. Now root has c_1 children.
// Moment 2: each of c_1 children gets k children. We prune extras.
// ...
// Moment p: done.
//
// So the operations happen at each moment, not just at the end.
// The total operations = sum over all moments of (number of prunes at that moment).
//
// At moment d (for d = 1, 2, ..., p):
//   All nodes at depth d-1 get k children.
//   Nodes at depth d-1 that are in T2 with c_i children: keep c_i, prune k - c_i.
//   Nodes at depth d-1 that are NOT in T2: they were already pruned.
//   Wait, nodes at depth d-1 that are in T2 but are leaves (c_i = 0): prune all k children.
//
// So at moment d, the number of prunes = sum over nodes i at depth d-1 in T2 of (k - c_i).
// But only for nodes that exist at depth d-1. Nodes at depth >= d don't exist yet.
//
// Wait, at moment d, nodes at depth d-1 exist (they were created at moment d-1 or earlier).
// So the prunes at moment d = sum_{i at depth d-1} (k - c_i).
//
// Total operations q = sum_{d=1}^{p} sum_{i at depth d-1} (k - c_i).
// = sum_{i=1}^{n} (k - c_i) [since every node is at some depth from 0 to p-1].
// = n*k - (n-1).
//
// But this gives 13 for the sample, not 4. So my analysis is wrong.
//
// The issue: at moment 1, only the root exists. It gets k children.
// We keep c_root children (for T2), prune k - c_root.
// At moment 2, the c_root children exist. Each gets k children.
// We keep c_i children for each, prune the rest.
// ...
//
// But the prunes at each moment are counted separately. So:
// Moment 1: root gets k children. Prune k - c_root = 3 - 2 = 1.
// Moment 2: nodes 2 and 5 exist. Node 2 gets k children, node 5 gets k children.
//   Node 2: prune k - c_2 = 3 - 2 = 1.
//   Node 5: prune k - c_5 = 3 - 1 = 2.
//   Total at moment 2: 1 + 2 = 3.
// Total operations: 1 + 3 = 4. ✓
//
// So q = sum_{d=0}^{p-1} sum_{i at depth d} (k - c_i).
// = sum_{i=1}^{n} (k - c_i).
// = n*k - (n-1).
// For the sample: 6*3 - 5 = 13. But expected is 4.
//
// Wait, I'm getting 4 from the manual calculation but 13 from the formula. Let me recheck.
//
// Manual: moment 1: 1 prune. moment 2: 3 prunes. Total: 4.
// Formula: sum(k - c_i) for all i.
// Node 1: k - c_1 = 3 - 2 = 1.
// Node 2: k - c_2 = 3 - 2 = 1.
// Node 3: k - c_3 = 3 - 0 = 3.
// Node 4: k - c_4 = 3 - 0 = 3.
// Node 5: k - c_5 = 3 - 1 = 2.
// Node 6: k - c_6 = 3 - 0 = 3.
// Total: 1+1+3+3+2+3 = 13.
//
// But in the manual calculation, nodes 3, 4, 6 are leaves at depth 2 = p.
// At moment 3 (which doesn't happen since p=2), they would get k children.
// But since p=2, moment 3 doesn't happen. So leaves at depth p don't get children.
//
// Ah, I see! The formula should only sum over nodes at depth 0 to p-1.
// Nodes at depth p (leaves at the deepest level) don't get children because
// the tree stops growing at moment p.
//
// Wait, but at moment p, ALL nodes at depth p-1 get k children. Including leaves of T2
// that are at depth p-1.
//
// Let me re-examine. At moment 2:
// Nodes at depth 1 (nodes 2 and 5) get k children.
// Node 2 gets 3 children, keeps 2 (nodes 3, 4), prunes 1.
// Node 5 gets 3 children, keeps 1 (node 6), prunes 2.
// Nodes at depth 2 (nodes 3, 4, 6) don't get children because moment 3 doesn't happen.
//
// So the prunes at moment 2 are only from nodes at depth 1, not depth 2.
// And nodes at depth 2 (leaves of T2 at the deepest level) don't contribute to prunes.
//
// So q = sum_{d=0}^{p-2} sum_{i at depth d} (k - c_i).
// Wait, at moment d+1, nodes at depth d get children. So:
// Moment 1: nodes at depth 0 (root) get children. Prunes = sum_{i at depth 0} (k - c_i).
// Moment 2: nodes at depth 1 get children. Prunes = sum_{i at depth 1} (k - c_i).
// ...
// Moment p: nodes at depth p-1 get children. Prunes = sum_{i at depth p-1} (k - c_i).
//
// But wait, for the sample, p=2. So:
// Moment 1: depth 0. Prunes = k - c_1 = 3-2 = 1.
// Moment 2: depth 1. Prunes = (k-c_2) + (k-c_5) = 1+2 = 3.
// Total: 4. ✓
//
// So q = sum_{d=0}^{p-1} sum_{i at depth d} (k - c_i).
// This is the same as sum_{i at depth 0 to p-1} (k - c_i).
// Nodes at depth p (leaves at max depth) don't contribute.
//
// For the sample: nodes at depth 0: {1}. Nodes at depth 1: {2,5}. Nodes at depth 2: {3,4,6}.
// q = (k-c_1) + (k-c_2) + (k-c_5) = 1+1+2 = 4. ✓
//
// So the formula is: q = sum over non-leaf nodes (or nodes at depth < p) of (k - c_i).
// = (number of non-leaf nodes) * k - (number of edges from non-leaf nodes).
//
// Actually, it's simpler: q = sum_{i: depth(i) < p} (k - c_i).
// For the sample: sum over {1,2,5} of (3-c_i) = 1+1+2 = 4. ✓
//
// Now, what about the case where T2's depth is less than the minimum moment?
// Actually, p IS the depth of T2. So all nodes at depth < p are non-leaf nodes
// (except possibly some leaves at intermediate depths).
//
// Wait, T2 can have leaves at intermediate depths. For example:
// 1-2, 1-3, 2-4. Here, node 3 is a leaf at depth 1, and node 4 is a leaf at depth 2.
// p = 2. Nodes at depth < p: {1, 2, 3}. But node 3 is a leaf (c_3 = 0).
// q = (k-c_1) + (k-c_2) + (k-c_3) = (k-2) + (k-1) + (k-0) = 3k - 3.
//
// But at moment 2, node 3 (a leaf at depth 1) also gets k children and we prune them.
// So node 3 contributes k prunes.
//
// Hmm, but in the sample, nodes 3, 4, 6 are at depth 2 = p, so they don't contribute.
// But node 3 in my example is at depth 1 < p = 2, so it does contribute.
//
// So the formula is correct: q = sum_{i: depth(i) < p} (k - c_i).
// But we need to handle the case where p is the maximum depth of T2.
//
// Actually, p is the minimum moment, which is the depth of T2 (height from root to deepest leaf).
// At moment p, all nodes at depth p-1 get k children. Nodes at depth p don't get children
// (since moment p+1 doesn't happen).
//
// So q = sum_{i: depth(i) <= p-1} (k - c_i) = sum_{i: depth(i) < p} (k - c_i).
// Wait, depth(i) <= p-1 is the same as depth(i) < p.
//
// For the sample: depth(1)=0, depth(2)=1, depth(5)=1, depth(3)=2, depth(4)=2, depth(6)=2.
// p = 2. Nodes with depth < 2: {1, 2, 5}.
// q = (3-2) + (3-2) + (3-1) = 1+1+2 = 4. ✓
//
// Great! So the algorithm is:
// 1. Build T2, compute depths and parent structure.
// 2. p = max depth of any node in T2.
// 3. q = sum over nodes with depth < p of (k - c_i).
//
// But wait, is p always equal to the depth of T2? What if k=1?
// For k=1, each node has at most 1 child. T2 must be a path.
// At moment t, the tree is a path of length t+1.
// If T2 is a path of length n, then p = n-1 (depth of deepest leaf).
//
// For k=1, q = sum_{i: depth(i) < p} (1 - c_i).
// For a path: c_i = 1 for non-leaf, c_i = 0 for leaf.
// q = sum_{i: depth(i) < p} (1 - c_i) = (p) * 1 - (p-1) = 1.
// Wait, for a path of length n: nodes at depth 0 to n-2 have c_i = 1, node at depth n-1 has c_i = 0.
// But depth n-1 = p, so nodes with depth < p are depths 0 to n-2.
// q = sum_{d=0}^{n-2} (1 - 1) = 0.
// But we need to prune the extra child at each step!
//
// Hmm, for k=1, each node gets exactly 1 child. If the node has 1 child in T2, no prune needed.
// If the node has 0 children in T2 (leaf), prune 1 child.
//
// For a path: every non-leaf node has 1 child. So no prunes needed. q = 0.
// But at the last node (leaf at depth p), it gets 1 child (since k=1). We need to prune it.
// Wait, the leaf at depth p is at the maximum depth. At moment p, nodes at depth p-1 get children.
// The leaf at depth p-1 gets 1 child (since k=1). If it's a leaf in T2 (c=0), we prune 1.
// So q includes this prune.
//
// For a path of length n (n nodes): leaf at depth n-2 has c=1 (it has child at depth n-1).
// Node at depth n-1 (leaf) doesn't get children (depth = p = n-1).
// So no prune for the deepest leaf.
// q = sum_{d=0}^{n-2} (1 - c_d) = sum_{d=0}^{n-2} (1-1) = 0. ✓ (no prunes needed for a path with k=1).
//
// But what about a tree where a leaf is at depth < p?
// For example: 1-2, 1-3, 2-4. k=2. p=2.
// Node 3 is a leaf at depth 1 < p=2.
// At moment 2, node 3 gets 2 children. c_3 = 0. Prune 2.
// q = (2-c_1) + (2-c_2) + (2-c_3) = (2-2) + (2-1) + (2-0) = 0+1+2 = 3.
//
// Let me verify: moment 1: root gets 2 children (nodes 2, 3). No prune (c_1=2).
// Moment 2: node 2 gets 2 children (node 4 + 1 extra). Prune 1.
//           node 3 gets 2 children (2 extras). Prune 2.
// Total: 0 + 1 + 2 = 3. ✓
//
// So the formula works. Let me implement it.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    long long k;
    cin >> n >> k;
    
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        // Make it a rooted tree with root 1
        // We need to determine parent-child relationships
        children[u].push_back(v);
        children[v].push_back(u);
    }
    
    // BFS to compute depths and parent structure
    vector<int> depth(n + 1, -1);
    vector<int> parent(n + 1, 0);
    vector<int> childCount(n + 1, 0);
    
    depth[1] = 0;
    parent[1] = 0;
    vector<int> queue = {1};
    int qi = 0;
    while (qi < (int)queue.size()) {
        int u = queue[qi++];
        for (int v : children[u]) {
            if (depth[v] == -1) {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                childCount[u]++;
                queue.push_back(v);
            }
        }
    }
    
    // p = max depth
    int p = 0;
    for (int i = 1; i <= n; i++) {
        if (depth[i] > p) p = depth[i];
    }
    
    // q = sum over nodes with depth < p of (k - childCount[i])
    long long q = 0;
    for (int i = 1; i <= n; i++) {
        if (depth[i] < p) {
            q += k - childCount[i];
        }
    }
    
    cout << p << " " << q << "\n";
    
    return 0;
}
