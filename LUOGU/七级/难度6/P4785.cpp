#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> x(n + 1);
    for (int i = 1; i <= n; i++) cin >> x[i];
    // The operation: at round k (k=2..n), can swap x[k] with x[k/2]
    // This forms a binary tree structure (heap-like)
    // We want lexicographically smallest sequence
    // Greedy: process from position 1 to n
    // For position i, we want the smallest possible value
    // The constraint: at round k, only x[k] and x[k/2] can be swapped
    // This means: after all operations, x[i] can be any value that was
    // originally in the subtree rooted at i in the binary tree

    // Binary tree: node i has children 2i and 2i+1
    // Subtree of i contains all nodes j where i is an ancestor of j
    // in the binary tree (j's binary representation starts with i's)

    // For lexicographic order: process positions 1, 2, 3, ...
    // At position i, we want the smallest available value from subtree(i)
    // After choosing, remove that value from all ancestor subtrees

    // Use a priority queue / multiset for each subtree
    // But we need to efficiently query and remove

    // Approach: for each position from 1 to n, find the subtree
    // and pick the minimum. Use a set to track available values.

    // For position i, subtree contains: i, 2i, 2i+1, 4i, 4i+1, 4i+2, 4i+3, ...
    // We need to find which of these are still unassigned

    // Use a BIT/segment tree approach:
    // Process positions in order. For position i, the available values
    // in subtree(i) are those originally at nodes in subtree(i) that
    // haven't been assigned yet.

    // Efficient approach: use a set of available positions
    // For each position i, find all nodes in subtree(i) that are still available
    // Pick the one with smallest x value

    // Since n can be up to 2*10^5, we need O(n log n)

    // Key insight: position i's subtree = {i*2^k + offset | ...}
    // The subtree of i in the binary tree:
    //   i, 2i, 2i+1, 4i, 4i+1, 4i+2, 4i+3, ...
    //   = all j where j >= i and the binary representation of j
    //     has i as a prefix (when written in binary)

    // For processing: maintain a sorted structure of (value, position)
    // For position i, iterate over subtree(i) nodes that are still available
    // and pick the minimum

    // Use a set sorted by value
    vector<pair<int, int>> vals; // (value, original position)
    for (int i = 1; i <= n; i++)
        vals.push_back({x[i], i});
    sort(vals.begin(), vals.end());

    // For each position i, we need to know which subtree nodes are still free
    // Use a DSU-like structure: next_free[i] = next position >= i in subtree that's free
    // But subtree nodes aren't contiguous...

    // Simpler approach: use a BIT over positions
    // Mark positions as used. For subtree of i, count available positions
    // and find the k-th available one

    // Actually, the subtree of i in the binary tree can be enumerated:
    // Start from i, then children 2i, 2i+1, then their children, etc.
    // But this is O(n) per query in worst case.

    // Better: use the observation that subtree(i) = {j : i is ancestor of j}
    // In a binary tree, i is ancestor of j iff floor(j / 2^k) = i for some k
    // Equivalently: j in [i * 2^k, (i+1) * 2^k - 1] for some k >= 0
    // And j <= n

    // So subtree(i) = union of intervals [i*2^k, min((i+1)*2^k - 1, n)] for k = 0, 1, 2, ...

    // For each position i (processed in order), find the minimum x[j] where j is in subtree(i) and j is unassigned.

    // Use a segment tree over positions to find min x[j] in a range
    // Then for each subtree interval, query the min, and take the overall min

    // Implementation:
    // Build segment tree over positions 1..n storing x[j]
    // For position i, enumerate subtree intervals and query min
    // Take the minimum across all intervals
    // Mark that position as used (set to INF in segtree)

    const int INF = 1e9 + 1;
    vector<int> seg(4 * (n + 1));
    function<void(int,int,int)> build = [&](int node, int l, int r) {
        if (l == r) { seg[node] = x[l]; return; }
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
        seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
    };
    build(1, 1, n);

    function<void(int,int,int,int,int)> update = [&](int node, int l, int r, int pos, int val) {
        if (l == r) { seg[node] = val; return; }
        int mid = (l + r) / 2;
        if (pos <= mid) update(node * 2, l, mid, pos, val);
        else update(node * 2 + 1, mid + 1, r, pos, val);
        seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
    };

    function<int(int,int,int,int,int)> query = [&](int node, int l, int r, int ql, int qr) -> int {
        if (ql > r || qr < l) return INF;
        if (ql <= l && r <= qr) return seg[node];
        int mid = (l + r) / 2;
        return min(query(node * 2, l, mid, ql, qr),
                   query(node * 2 + 1, mid + 1, r, ql, qr));
    };

    vector<int> ans(n + 1);
    vector<bool> used(n + 1, false);

    for (int i = 1; i <= n; i++) {
        // Find minimum value in subtree(i)
        int best_val = INF, best_pos = -1;
        for (int k = 0; ; k++) {
            long long left = (long long)i * (1LL << k);
            long long right = (long long)(i + 1) * (1LL << k) - 1;
            if (left > n) break;
            int r = min((long long)n, right);
            int q = query(1, 1, n, (int)left, r);
            if (q < best_val) {
                best_val = q;
                // Find the actual position with this value
                // We need to search for it
                // For simplicity, just use the value; the position will be determined
                // by finding which node in the interval has this value
            }
        }
        ans[i] = best_val;
        // Find and mark the position
        // Search through subtree intervals for the position with best_val
        for (int k = 0; ; k++) {
            long long left = (long long)i * (1LL << k);
            long long right = (long long)(i + 1) * (1LL << k) - 1;
            if (left > n) break;
            int r = min((long long)n, right);
            // Find position with value best_val in [left, r]
            // Linear scan (could be optimized with a map)
            for (int j = (int)left; j <= r; j++) {
                if (!used[j] && x[j] == best_val) {
                    used[j] = true;
                    update(1, 1, n, j, INF);
                    goto done;
                }
            }
        }
        done:;
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
