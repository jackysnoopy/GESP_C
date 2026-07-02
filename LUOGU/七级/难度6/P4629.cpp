#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2005;
int n;
long long d[MAXN], c[MAXN];
vector<int> adj[MAXN];
long long dp[MAXN][2]; // dp[u][0]: u activated externally, dp[u][1]: u activated by parent

void dfs(int u, int p) {
    dp[u][0] = d[u]; // activate u externally
    dp[u][1] = 0;    // u activated by parent, no cost for u itself
    long long extra = 0; // extra cost for children when u is activated by parent

    vector<long long> diffs;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        // If u is activated externally, children need max(0, d_v - c_u) each
        // If u is activated by parent, children need max(0, d_v - c_u) each
        // Wait, when u is activated, it sends c_u to each unactivated child
        // So child v needs max(0, d_v - c_u) external energy
        long long need_v = max(0LL, d[v] - c[u]);

        // Child v can be activated externally (cost dp[v][0]) or by u (cost dp[v][1])
        // If v is activated by u: cost = max(0, d[v] - c[u]) + dp[v][1] ... no
        // Actually: if v is activated by u, v doesn't need external energy from u
        // but v might need to activate its own children

        // Let me reconsider the DP states:
        // dp[u][0] = min cost for subtree u when u is activated by paying d[u] externally
        // dp[u][1] = min cost for subtree u when u is activated by parent (free for u)
        // When u is activated (either way), it sends c[u] to each child
        // Child v then needs max(0, d[v] - c[u]) external energy if activated externally
        // Or child v can be activated by u if d[v] <= c[u] (free)

        // For child v:
        // Option 1: v activated by u (free for v if c[u] >= d[v])
        //   cost = dp[v][1] (v's subtree cost when v is "free")
        // Option 2: v activated externally
        //   cost = d[v] + dp[v][0] ... no, dp[v][0] already includes d[v]

        // Let me redefine:
        // dp[u][0] = min cost for subtree u when u pays d[u] externally
        // dp[u][1] = min cost for subtree u when u is free (activated by parent)

        // When u is activated:
        // For each child v:
        //   If v is activated by u: v is free, cost = dp[v][1]
        //   If v is activated externally: cost = dp[v][0]
        //   v chooses the cheaper option

        // But wait: when u is activated, it sends c[u] to v.
        // If c[u] >= d[v], v can be free (activated by u)
        // If c[u] < d[v], v needs d[v] - c[u] external energy

        // Actually the DP should be:
        // dp[u][0] = d[u] + sum over children v of min(dp[v][0], dp[v][1])
        //   (u pays d[u], children choose freely)
        // dp[u][1] = sum over children v of:
        //   if c[u] >= d[v]: min(dp[v][0], dp[v][1]) (v can be free)
        //   else: min(dp[v][0], d[v]-c[u] + dp[v][1]) (v needs some external)

        // Hmm, this doesn't quite capture the energy transfer correctly.
        // Let me think more carefully.

        // When u is activated (by any means), it sends c[u] energy to each neighbor.
        // For child v, this c[u] energy reduces v's need.
        // v's effective need = max(0, d[v] - c[u])
        // v can then be activated externally (paying effective need + dp[v][0])
        // or v can activate its own children (if v is activated, it sends c[v])

        // Actually the key insight: when v is activated (by u or externally),
        // v sends c[v] to its children. The cost for v's subtree depends on
        // whether v paid externally or was free.

        // dp[v][0] = min cost for v's subtree when v pays d[v] externally
        // dp[v][1] = min cost for v's subtree when v is free

        // When u is activated and sends c[u] to v:
        // v's external cost = max(0, d[v] - c[u])
        // v can be "free" if c[u] >= d[v], cost = dp[v][1]
        // v can pay the remaining externally: cost = max(0, d[v]-c[u]) + dp[v][0]

        // Wait, dp[v][0] already includes d[v]. So:
        // If v is activated by u with help c[u]:
        //   v pays max(0, d[v]-c[u]) externally
        //   v's subtree cost = max(0, d[v]-c[u]) + dp[v][0] - d[v] ... no

        // Let me redefine clearly:
        // dp[u][0] = min total energy for subtree rooted at u,
        //            when u is activated by paying d[u] externally
        // dp[u][1] = min total energy for subtree rooted at u,
        //            when u is activated for free (by parent's energy)

        // When u is activated (regardless of how), u sends c[u] to each child.
        // For child v:
        //   v's activation cost = max(0, d[v] - c[u])
        //   If v is activated externally: total for v's subtree = max(0, d[v]-c[u]) + (dp[v][0] - d[v])
        //     Wait, dp[v][0] = d[v] + children cost. If v pays max(0,d[v]-c[u]) instead of d[v],
        //     then v's subtree cost = max(0,d[v]-c[u]) + children cost when v is activated
        //     = max(0,d[v]-c[u]) + (dp[v][0] - d[v])
        //   If v is activated by u (free): total = dp[v][1]

        // So for child v:
        //   cost if v activated externally = max(0,d[v]-c[u]) + dp[v][0] - d[v]
        //     = dp[v][0] - min(d[v], c[u])
        //   cost if v activated by u = dp[v][1]
        //   v chooses min of these two

        long long cost_ext = dp[v][0] - min(d[v], c[u]);
        long long cost_free = dp[v][1];
        dp[u][0] += min(cost_ext, cost_free);
    }

    // For dp[u][1], u is free, but u still sends c[u] to children
    // Same calculation as dp[u][0] but without adding d[u]
    dp[u][1] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        long long cost_ext = dp[v][0] - min(d[v], c[u]);
        long long cost_free = dp[v][1];
        dp[u][1] += min(cost_ext, cost_free);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> d[i];
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    cout << dp[1][0] << "\n";
    return 0;
}
