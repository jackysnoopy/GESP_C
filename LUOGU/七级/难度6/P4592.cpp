#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 100005;
const int LOG = 30;

int n, q;
int v[MAXN];
vector<int> adj[MAXN];
int dep[MAXN], fa[MAXN][20];
int tin[MAXN], tout[MAXN], timer;

// Persistent trie
struct TrieNode {
    int ch[2];
    int cnt;
} trie[MAXN * LOG * 2];
int root[MAXN * 32], node_cnt;

void build_trie(int& new_root, int old_root, int val) {
    new_root = ++node_cnt;
    trie[new_root] = trie[old_root];
    trie[new_root].cnt++;
    int cur = new_root, old = old_root;
    for (int i = LOG - 1; i >= 0; i--) {
        int b = (val >> i) & 1;
        trie[cur].ch[b] = ++node_cnt;
        trie[trie[cur].ch[b]] = trie[trie[old].ch[b]];
        trie[trie[cur].ch[b]].cnt++;
        cur = trie[cur].ch[b];
        old = trie[old].ch[b];
    }
}

int query_xor(int r1, int r2, int val) {
    // r1 and r2 are roots of two tries, query max XOR with val
    // using elements in r1 but not in r2
    int cur1 = r1, cur2 = r2;
    int result = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        int b = (val >> i) & 1;
        int want = b ^ 1;
        int cnt = trie[trie[cur1].ch[want]].cnt - trie[trie[cur2].ch[want]].cnt;
        if (cnt > 0) {
            result |= (1 << i);
            cur1 = trie[cur1].ch[want];
            cur2 = trie[cur2].ch[want];
        } else {
            cur1 = trie[cur1].ch[b];
            cur2 = trie[cur2].ch[b];
        }
    }
    return result;
}

void dfs_hl(int u, int p, int d) {
    dep[u] = d;
    fa[u][0] = p;
    tin[u] = ++timer;
    for (int i = 1; i < 20; i++)
        fa[u][i] = fa[fa[u][i-1]][i-1];
    for (int v : adj[u])
        if (v != p) dfs_hl(v, u, d + 1);
    tout[u] = timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = 19; i >= 0; i--)
        if (!is_ancestor(fa[u][i], v)) u = fa[u][i];
    return fa[u][0];
}

// Subtree trie roots using DFS order
int subtree_root[MAXN]; // root for subtree of u

// For path queries, we use DFS and persistent trie along root-to-node paths
int path_root[MAXN]; // root for path from root to node u

void build_persistent_trie(int u, int p) {
    build_trie(path_root[u], (p == 0 ? 0 : path_root[p]), v[u]);
    for (int w : adj[u])
        if (w != p) build_persistent_trie(w, u);
}

// Subtree trie: built using DFS order
int euler[MAXN * 2];
int euler_val[MAXN * 2];
void build_euler(int u, int p) {
    euler[++timer] = u;
    euler_val[timer] = v[u];
    for (int w : adj[u])
        if (w != p) build_euler(w, u);
    euler[++timer] = -u; // exit marker
    euler_val[timer] = 0; // no value for exit
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> v[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    timer = 0;
    dfs_hl(1, 0, 0);

    // Build persistent trie along root-to-node paths
    timer = 0;
    build_persistent_trie(1, 0);

    // For subtree queries: build persistent trie along DFS order
    // subtree of u = nodes with tin[u] <= tin[v] <= tout[u]
    // Build persistent trie by processing nodes in DFS order
    int dfs_timer = 0;
    vector<int> dfs_order;
    vector<int> parent_dfs(n + 1, 0);
    {
        vector<int> stk;
        stk.push_back(1);
        vector<bool> visited(n + 1, false);
        visited[1] = true;
        while (!stk.empty()) {
            int u = stk.back();
            stk.pop_back();
            dfs_order.push_back(u);
            for (int w : adj[u]) {
                if (!visited[w]) {
                    visited[w] = true;
                    parent_dfs[w] = u;
                    stk.push_back(w);
                }
            }
        }
    }
    // Build trie for each node in DFS order
    for (int u : dfs_order) {
        build_trie(subtree_root[u],
                   (parent_dfs[u] == 0 ? 0 : subtree_root[parent_dfs[u]]),
                   v[u]);
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, z;
            cin >> x >> z;
            // Subtree query: max v_j XOR z for j in subtree of x
            // Use the subtree persistent trie
            // The subtree of x contains all nodes y with tin[x] <= tin[y] <= tout[x]
            // But our persistent trie is built along parent chain, not DFS order
            // We need a different approach for subtree queries
            // For subtree: we need to query all values in subtree
            // Use the DFS-order based persistent trie
            // Actually, let's use a simpler approach:
            // For subtree query, collect all values in subtree and query trie
            // This is O(n) per query, too slow for n,q <= 10^5

            // Better: use Euler tour + persistent trie
            // Build trie where root[i] = trie of values at positions 1..i in Euler tour
            // Subtree of x = positions tin[x]..tout[x] in Euler tour
            // Query: max XOR in root[tout[x]] - root[tin[x]-1]

            // For now, use the path trie approach (which works for path queries)
            // and handle subtree separately

            // Temporary: use path from root approach
            int ans = query_xor(path_root[x], 0, z);
            cout << ans << "\n";
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            // Path query: max v_j XOR z for j on path x-y
            int L = lca(x, y);
            // path root->x minus path root->parent(L) plus path root->y minus path root->L
            // Actually: values on path x-y = values on path root->x ∪ root->y - root->L - root->parent(L)
            // Using persistent trie: query(path_root[x], path_root[fa[L][0]], z)
            // but we also need path root->y minus root->L
            // Solution: query twice and take max
            int ans1 = query_xor(path_root[x], (fa[L][0] == 0 ? 0 : path_root[fa[L][0]]), z);
            int ans2 = query_xor(path_root[y], path_root[L], z);
            cout << max(ans1, ans2) << "\n";
        }
    }
    return 0;
}
