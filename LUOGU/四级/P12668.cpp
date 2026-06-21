#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

ll power(ll base, ll exp, ll mod) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll mod) {
    return power(a, mod - 2, mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, m, k;
    cin >> n >> m;
    cin >> k;
    
    if (k == 0) {
        // Only level 0 with n+m balls
        // Probability of black = n / (n+m)
        cout << n % MOD * modInverse((n + m) % MOD, MOD) % MOD << endl;
        return 0;
    }
    
    ll a1, d, x;
    cin >> a1 >> d >> x;
    
    vector<ll> a(k + 1);
    a[1] = a1;
    for (ll i = 2; i <= k; i++) {
        a[i] = ((a[i-1] - d) ^ x);
    }
    
    // Compute the branching factors for the optimal tree
    // b_i = a_i - a_{i+1} + 1 for i < k, b_k = a_k
    // Actually, let me compute the probabilities for each level
    
    // The optimal tree has:
    // - One "main" path with branching b_i at level i
    // - (a_i - 1) "narrow" paths at level i, each with branching 1
    
    // Probability of a leaf on the main path at level 0:
    // P_main = product_{i=0}^{k} 1/b_i
    // where b_0 = (n+m) - a_1 + 1, b_i = a_i - a_{i+1} + 1 for 1 <= i < k, b_k = a_k
    
    // Probability of a leaf on a narrow path at level i (1 <= i <= k):
    // P_narrow_i = product_{j=i}^{k} 1/b_j (above level i, same as main; at level i, branching 1; below, branching 1)
    // Wait, the narrow path at level i has 1 child at level i-1, which has 1 child at level i-2, etc.
    // So the probability is: product_{j=i}^{k} 1/b_j.
    
    // Hmm, let me reconsider. The narrow path at level i:
    // - At level k: root has a_k children. Main path goes through one. Narrow path goes through the same one.
    //   Probability: 1/a_k = 1/b_k.
    // - At level k-1: main path node has b_{k-1} children. Narrow path goes through one of them.
    //   If the narrow level-i node is a child of the main path node at level i+1:
    //   Probability at level i+1: 1/b_{i+1}.
    // - At level i: the narrow node has 1 child. Probability: 1/1 = 1.
    // - Below level i: all branching is 1. Probability: 1.
    
    // So P_narrow_i = product_{j=i+1}^{k} 1/b_j.
    // Wait, for i=k: P_narrow_k = 1 (no levels above).
    // But the narrow level-k node is a child of the root. Probability: 1/a_k = 1/b_k.
    // So P_narrow_k = 1/b_k.
    
    // Hmm, let me re-examine. The narrow paths at level i are the non-main nodes at level i.
    // Each non-main node at level i is a child of the main path node at level i+1.
    // So the probability of reaching a non-main node at level i is:
    // 1/a_k * 1/b_{k-1} * ... * 1/b_{i+1} * 1/b_{i+1} ... wait, that's wrong.
    
    // Let me think step by step.
    // Root has a_k children (level-k nodes). Main path goes through one. Others are non-main.
    // Main path level-k node has b_{k-1} = a_{k-1} - a_k + 1 children (level-(k-1) nodes).
    // Non-main level-k nodes have 1 child each.
    
    // A non-main level-k node: probability 1/a_k.
    // Its child (level-(k-1) node): probability 1/1 = 1.
    // That child's child (level-(k-2) node): probability 1/1 = 1.
    // ... down to level 0.
    // So P_narrow_k = 1/a_k = 1/b_k.
    
    // A non-main level-(k-1) node (child of main path level-k node):
    // Probability at level k: 1/a_k = 1/b_k.
    // Probability at level k-1: 1/b_{k-1} (main path node has b_{k-1} children).
    // Wait, the non-main level-(k-1) node is one of the b_{k-1} children of the main path level-k node.
    // So probability at level k-1: 1/b_{k-1}.
    // Below level k-1: all branching 1. Probability: 1.
    // So P_narrow_{k-1} = 1/b_k * 1/b_{k-1}.
    
    // Hmm, but I said the non-main level-(k-1) node has 1 child. So its child (level-(k-2) node)
    // has probability 1/1 = 1 at level k-2.
    // But the main path level-(k-1) node has b_{k-2} children. So the main path leaf has
    // probability 1/b_{k-2} at level k-2.
    
    // I think the issue is that I'm confusing the levels. Let me re-index.
    
    // Level k: top (root's children).
    // Level k-1: next level down.
    // ...
    // Level 1: second from bottom.
    // Level 0: bottom (leaves).
    
    // Root has a_k children at level k.
    // Level k node has some children at level k-1.
    // ...
    // Level 1 node has some children at level 0 (leaves).
    
    // Main path: root -> level-k node -> level-(k-1) node -> ... -> level-1 node -> leaf.
    
    // At level k: main path node has b_{k-1} = a_{k-1} - a_k + 1 children at level k-1.
    // Non-main level-k nodes have 1 child each.
    
    // At level k-1: main path node has b_{k-2} = a_{k-2} - a_{k-1} + 1 children at level k-2.
    // Non-main level-(k-1) nodes have 1 child each.
    
    // ...
    
    // At level 1: main path node has b_0 = a_0 - a_1 + 1 = (n+m) - a_1 + 1 children at level 0.
    // Non-main level-1 nodes have 1 child each.
    
    // Probability of main path leaf:
    // P_main = 1/a_k * 1/b_{k-1} * 1/b_{k-2} * ... * 1/b_0.
    
    // Probability of non-main leaf at level i (child of non-main level-i node):
    // The non-main level-i node is a child of the main path level-(i+1) node.
    // Probability up to level i+1: 1/a_k * 1/b_{k-1} * ... * 1/b_{i+1}.
    // At level i: the non-main node is one of b_i children. Probability 1/b_i.
    // Wait, no. The non-main level-i node is a child of the main path level-(i+1) node.
    // The main path level-(i+1) node has b_i children at level i.
    // The non-main level-i node is one of them. Probability 1/b_i.
    // Below level i: all branching 1. Probability: 1.
    // So P_non_main_i = 1/a_k * 1/b_{k-1} * ... * 1/b_{i+1} * 1/b_i.
    // = P_main * b_0 * b_1 * ... * b_{i-1} / (1 * 1 * ... * 1).
    // Hmm, this doesn't simplify nicely.
    
    // Actually, P_main = product_{j=0}^{k} 1/b_j (where b_k = a_k, b_j = a_j - a_{j+1} + 1 for j < k).
    // Wait, I need to be more careful about the indexing.
    
    // Let me define c_j for j = 0, 1, ..., k:
    // c_k = a_k (branching at level k for main path).
    // c_j = a_j - a_{j+1} + 1 for j = 0, 1, ..., k-1.
    // Wait, for j=0: c_0 = a_0 - a_1 + 1 = (n+m) - a_1 + 1.
    
    // P_main = product_{j=0}^{k} 1/c_j.
    
    // For a non-main leaf at level i:
    // It's under a non-main level-i node, which is a child of the main path level-(i+1) node.
    // Probability: product_{j=i+1}^{k} 1/c_j * 1/c_i * 1 * ... * 1 = product_{j=i}^{k} 1/c_j.
    // Wait, that's the same as P_main for i=0.
    
    // Hmm, let me recalculate for i=1:
    // Non-main level-1 node is a child of main path level-2 node.
    // Probability at level k: 1/c_k.
    // Probability at level k-1: 1/c_{k-1}.
    // ...
    // Probability at level 2: 1/c_2.
    // Probability at level 1: the non-main level-1 node is one of c_1 children of the main path level-2 node.
    // Wait, c_1 = a_1 - a_2 + 1. The main path level-2 node has c_1 children at level 1.
    // The non-main level-1 node is one of them. Probability: 1/c_1.
    // Below level 1: 1 child each. Probability: 1.
    // So P_non_main_1 = product_{j=1}^{k} 1/c_j.
    // P_main = product_{j=0}^{k} 1/c_j.
    // P_non_main_1 / P_main = c_0.
    // So P_non_main_1 = P_main * c_0.
    
    // For i=2:
    // Non-main level-2 node is a child of main path level-3 node.
    // Probability: product_{j=2}^{k} 1/c_j.
    // P_non_main_2 / P_main = c_0 * c_1.
    // So P_non_main_2 = P_main * c_0 * c_1.
    
    // In general: P_non_main_i = P_main * product_{j=0}^{i-1} c_j.
    
    // And the number of non-main leaves at level i is a_i - 1.
    
    // So the optimal strategy:
    // 1. Sort all leaves by probability (descending).
    // 2. Put black balls on the highest-probability leaves.
    // 3. Put white balls on the rest.
    
    // The leaves and their probabilities:
    // - Non-main leaves at level i: a_i - 1 leaves, probability P_main * prod_{j=0}^{i-1} c_j.
    // - Main path leaves: c_0 leaves, probability P_main.
    
    // Sort by probability: non-main leaves at level k have highest probability (prod_{j=0}^{k-1} c_j),
    // then level k-1 (prod_{j=0}^{k-2} c_j), ..., then level 1 (c_0), then main path (1).
    
    // So the order is: level k, level k-1, ..., level 1, main path.
    
    // For each level i (from k down to 1):
    //   Put min(a_i - 1, remaining_black) black balls. Each has probability P_main * prod_{j=0}^{i-1} c_j.
    // Then put remaining black balls on main path leaves. Each has probability P_main.
    
    // Total black probability = sum_{i=k}^{1} min(a_i - 1, rem) * P_main * prod_{j=0}^{i-1} c_j
    //                        + max(0, n - total_narrow) * P_main.
    
    // Let me compute this.
    
    vector<ll> c(k + 1);
    c[k] = a[k];
    for (ll i = 0; i < k; i++) {
        c[i] = a[i] - a[i + 1] + 1;
    }
    // Wait, a[0] = n + m.
    // Actually, the problem says a_i for i = 1..k. And a_0 = n + m (the number of balls).
    // But the problem gives a_1, and computes a_2, ..., a_k.
    // And the leaves are n + m balls at level 0.
    
    // So c_0 = (n+m) - a_1 + 1.
    // c_i = a_i - a_{i+1} + 1 for i = 1, ..., k-1.
    // c_k = a_k.
    
    c[0] = (n + m) - a[1] + 1;
    for (ll i = 1; i < k; i++) {
        c[i] = a[i] - a[i + 1] + 1;
    }
    c[k] = a[k];
    
    // P_main = product_{j=0}^{k} 1/c_j mod MOD.
    ll P_main = 1;
    for (ll j = 0; j <= k; j++) {
        P_main = P_main * modInverse(c[j] % MOD, MOD) % MOD;
    }
    
    // Compute total black probability
    ll total = 0;
    ll remaining = n;
    
    // Process levels from k down to 1
    vector<ll> prefixProd(k + 1, 1);
    for (ll i = 1; i <= k; i++) {
        prefixProd[i] = prefixProd[i - 1] * (c[i - 1] % MOD) % MOD;
    }
    
    for (ll i = k; i >= 1 && remaining > 0; i--) {
        ll numNarrow = a[i] - 1;
        ll use = min(remaining, numNarrow);
        ll prob = P_main * prefixProd[i] % MOD;
        total = (total + use % MOD * prob) % MOD;
        remaining -= use;
    }
    
    // Remaining black balls go on main path leaves
    if (remaining > 0) {
        total = (total + remaining % MOD * P_main) % MOD;
    }
    
    cout << total % MOD << endl;
    
    return 0;
}
