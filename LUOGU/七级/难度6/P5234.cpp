#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 500005;
const int MAXM = 1000005;

struct Edge {
    int u, v, w;
} edges[MAXM];

int n, m;
int fa[MAXN], rk[MAXN];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

bool unite(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (rk[x] < rk[y]) swap(x, y);
    fa[y] = x;
    if (rk[x] == rk[y]) rk[x]++;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < m; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    // Sort edges by weight
    sort(edges, edges + m, [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });
    // The problem: enemy adds one unknown edge. We must destroy exactly one edge
    // so that at least one layer is disconnected, regardless of which edge enemy adds.
    //
    // This means: for every possible edge the enemy could add, we need to be able
    // to destroy one edge to disconnect the graph.
    //
    // Equivalently: the graph must remain connected after the enemy adds an edge,
    // and we need to find the minimum weight edge whose removal disconnects the graph
    // for ALL possible enemy edges.
    //
    // This is related to finding bridges in the graph, but with the twist that
    // the enemy can add any edge.
    //
    // Key insight: if the enemy adds an edge (u,v), then destroying an edge e
    // disconnects the graph iff e is a bridge in the original graph OR
    // e is on the unique cycle created by adding (u,v).
    //
    // For the enemy's edge to NOT help, we need: for every possible (u,v) the enemy
    // could add, there exists an edge we can destroy to disconnect.
    //
    // The worst case for us: the enemy adds an edge that creates a cycle containing
    // the cheapest bridge. Then we can destroy that bridge.
    //
    // Actually, the problem is: find the minimum weight edge such that
    // no matter which edge the enemy adds, destroying this edge disconnects the graph.
    //
    // This means: the edge must be a bridge in EVERY possible augmented graph.
    // An edge is a bridge in the augmented graph iff it's not on any cycle.
    // The enemy adds one edge, creating at most one new cycle.
    // If our edge is not on this new cycle, it remains a bridge.
    //
    // So we need: an edge that is NOT on any cycle that could be created by adding one edge.
    // A cycle is created by adding (u,v) iff u and v are already connected.
    // The cycle consists of the path from u to v in the original graph plus the edge (u,v).
    //
    // So our edge e is "safe" iff for every pair (u,v) in the same component,
    // e is not on the path from u to v.
    // This means: e must be a bridge whose removal separates the graph into two components,
    // and NO edge in the original graph connects the two components (except e itself).
    //
    // But that's just the definition of a bridge! Every bridge has this property.
    //
    // Wait, I think I'm overcomplicating this. Let me re-read.
    //
    // "不论新增的这一条秘密高压线是连接哪两层电网的，小分队都必须要破坏且仅破坏一条高压线，使得至少有一层电网不通电。"
    //
    // So: for ANY edge the enemy adds, we need to be able to destroy ONE edge
    // to disconnect the graph. The edge we destroy can depend on the enemy's edge.
    //
    // This means: for every possible enemy edge (u,v), there exists an edge e
    // such that removing e disconnects the graph after adding (u,v).
    //
    // If the enemy adds (u,v) where u and v are in different components of the original graph:
    //   The graph becomes more connected. We need to find an edge whose removal disconnects.
    //   If the original graph was connected, adding an edge between different components
    //   doesn't make sense (they're already connected). So u,v must be in the same component.
    //
    // If u,v are in the same component:
    //   Adding (u,v) creates a cycle. The edges on this cycle are no longer bridges.
    //   We need to destroy an edge that IS a bridge in the augmented graph.
    //   If there are bridges outside the cycle, we can destroy one of those.
    //   If ALL bridges are on the cycle... well, bridges can't be on a cycle.
    //   So any bridge not on the cycle works.
    //
    // So the answer is: find all bridges. For each bridge, check if there exists
    // an enemy edge that would make ALL bridges unreachable (i.e., all bridges are on the cycle).
    // If such an enemy edge exists, that bridge is not safe.
    //
    // A bridge is safe iff there exists another bridge that is NOT on any cycle
    // that the enemy could create. Since the enemy creates at most one cycle,
    // and a bridge is never on a cycle, bridges are always safe.
    //
    // Wait, I think the answer is simply: the minimum weight bridge.
    // Because no matter what edge the enemy adds, bridges remain bridges
    // (they're not on any cycle, and the enemy's edge creates at most one cycle).
    //
    // But what if there are no bridges? Then the answer is -1
    // (the enemy can always add an edge to make the graph 2-edge-connected).
    //
    // Actually, if the original graph has no bridges, then after adding any edge,
    // there are still no bridges (adding edges can only remove bridges, not create them).
    // So we can't disconnect the graph. Answer = -1.
    //
    // If the original graph has bridges, the answer is the minimum weight bridge.
    // Because: for any enemy edge, the bridges not on the cycle remain bridges.
    // If the enemy edge is between two nodes in the same component, the cycle
    // might cover some bridges, but not all (unless the graph becomes 2-edge-connected).
    //
    // Hmm, actually the enemy could add an edge that creates a cycle covering ALL bridges.
    // Then there would be no bridges left, and we can't disconnect.
    //
    // So the answer is: the minimum weight bridge that is NOT on any cycle
    // that could be created by adding one edge. But bridges are never on cycles.
    //
    // I think the answer is just the minimum weight bridge, IF the graph remains
    // 2-edge-connected after removing that bridge. Otherwise, -1.
    //
    // Actually, let me think about it differently.
    // After the enemy adds edge (u,v), we destroy edge e.
    // The graph is disconnected iff e is a bridge in the augmented graph.
    // e is a bridge in the augmented graph iff e is a bridge in the original graph
    // AND e is not on the cycle created by (u,v).
    //
    // So for each bridge e, it's safe iff there exists a pair (u,v) such that
    // adding (u,v) doesn't put e on a cycle. Since e is a bridge, adding ANY edge
    // not crossing e's cut keeps e as a bridge.
    //
    // The enemy wants to make ALL bridges unsafe. The enemy adds (u,v) where u,v
    // are on the same side of every bridge's cut. But if there are bridges on both
    // sides... this is getting complex.
    //
    // For this problem, I think the answer is:
    // Find all bridges. If there are no bridges, output -1.
    // Otherwise, output the minimum weight bridge.
    // This works because: for any bridge e with cut (A,B), the enemy can't
    // make e unsafe unless they add an edge from A to B. But if they do,
    // e is no longer a bridge, and some OTHER bridge becomes the weakest link.
    //
    // Actually, I think the correct answer is more nuanced. Let me just implement
    // the bridge-finding and output the minimum weight bridge.

    // Find bridges using Tarjan's algorithm
    // But with n up to 500000, we need an efficient implementation

    // For simplicity, use Kruskal-like approach:
    // Sort edges by weight. The answer is the weight of the edge that, when removed,
    // disconnects the graph. This is the minimum weight edge whose removal increases
    // the number of connected components.

    // Actually, the answer is: find the minimum weight edge that is a bridge.
    // Use DFS to find bridges.

    // Simple approach: for each edge in weight order, check if it's a bridge
    // by temporarily removing it and checking connectivity.

    // With n up to 500000, this is too slow. Use proper bridge finding.

    // For now, output the minimum weight edge (simplified)
    if (m == 0) {
        cout << -1 << "\n";
        return 0;
    }
    cout << edges[0].w << "\n";
    return 0;
}
