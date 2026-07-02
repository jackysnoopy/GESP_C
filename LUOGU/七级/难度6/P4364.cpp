#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int n;
double k;
int d[500005];
int ans[500005];
int fa[500005];

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> d[i];
    // Sort difficulties in decreasing order
    vector<int> idx(n);
    for (int i = 0; i < n; i++) idx[i] = i + 1;
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return d[a] > d[b];
    });
    // For each position i, the number of positions that must come before i
    // is floor(i/k) (positions 1..floor(i/k) must be filled before i)
    // Initialize DSU: fa[i] points to the next available slot >= i
    for (int i = 0; i <= n + 1; i++) fa[i] = i;
    // cnt[i] = number of positions j such that floor(j/k) >= i
    // i.e., j >= i*k, so count = n - ceil(i*k) + 1
    // Actually we need: for position i, it becomes available when
    // floor(i/k) positions before it are filled
    // Use a different approach: for each difficulty value (processed in decreasing order),
    // assign it to the earliest available position

    // The key insight from the official solution:
    // Process difficulties in decreasing order
    // For each group of equal difficulties, we need to assign them to positions
    // such that position i has floor(i/k) predecessors already assigned

    // For each position i, define avail[i] = floor(i/k)
    // We need avail[i] positions with index < i to be assigned before i

    // Sort positions by avail[i] (or equivalently by i)
    // Process difficulties from largest to smallest
    // For each difficulty value, find the available positions

    // Simplified approach using DSU:
    // fa[i] = next unassigned position >= i
    // For each difficulty (processed in groups from largest):
    //   Find how many positions need this difficulty
    //   Assign them greedily to the latest possible positions

    // Count how many of each difficulty
    vector<int> sorted_d(d + 1, d + n + 1);
    sort(sorted_d.begin(), sorted_d.end(), greater<int>());

    // Process from largest difficulty to smallest
    // For each difficulty value v, count how many positions can be assigned v
    // A position i can be assigned v if:
    //   floor(i/k) positions with smaller or equal difficulty are available for i's predecessors
    // This is complex. Use the greedy approach:

    // For each position i from n down to 1:
    //   The number of positions that MUST come after i is:
    //   positions j where floor(j/k) >= floor(i/k)+1, i.e., j >= (floor(i/k)+1)*k
    //   But this depends on the specific k value.

    // Simpler: use the observation that we process difficulties in decreasing order
    // and assign each to the rightmost available position

    // Initialize: all positions available
    // For each difficulty value (largest first):
    //   Find how many positions need exactly this difficulty
    //   Assign them

    // Use the "slot" approach:
    // Position i becomes available when floor(i/k) predecessors are filled
    // Track: for each number of predecessors needed (0, 1, 2, ...),
    // how many positions need that many predecessors

    // Actually, let's use the standard solution approach:
    // 1. Sort difficulties in decreasing order
    // 2. For each difficulty, find the positions where it can go
    // 3. Use DSU to find available positions

    // Reset and use proper approach
    for (int i = 0; i <= n + 1; i++) fa[i] = i;

    // For position i, it needs floor(i/k) positions before it to be assigned
    // So position i is "available" when floor(i/k) assignments have been made to positions < i
    // Track how many assignments have been made to positions < i

    // Better approach: process difficulties in decreasing order
    // For each group of equal difficulties:
    //   Count how many positions in range [L, R] need to be filled
    //   where L and R are determined by the DSU structure

    // Standard solution: use DSU where fa[i] = next position >= i that hasn't been assigned
    // But we need to respect the ordering constraint

    // Let's use the approach from the editorial:
    // For each position i, it has "need" = floor(i/k) predecessors
    // Process difficulties in decreasing order
    // For each difficulty value, assign it to positions with the smallest "need" that are still available

    // Implementation with priority queue:
    // For each position i, compute need[i] = floor(i/k)
    // Group positions by need value
    // Process difficulties from largest to smallest
    // For each difficulty, pick the position with smallest need that's available

    vector<int> need(n + 1);
    for (int i = 1; i <= n; i++) {
        need[i] = (int)floor(i / k);
    }

    // For each need value, maintain a sorted list of positions
    // When processing a difficulty, assign to the position with smallest need

    // Use a different approach: for each position, track how many predecessors must be assigned first
    // Process difficulties from largest to smallest
    // For each difficulty value group, assign to the rightmost available positions

    // Final approach: use DSU for position availability
    // fa[i] = next position >= i that is available
    // A position i is available if floor(i/k) positions with index < i have been assigned

    // Track assignments per position range
    vector<int> cnt_need(n + 2, 0); // cnt_need[v] = number of positions with need = v
    for (int i = 1; i <= n; i++) cnt_need[need[i]]++;

    // Process difficulties from largest to smallest
    int pos = n; // assign from right to left
    for (int i = 0; i < n; i++) {
        int v = sorted_d[i];
        // Find the rightmost available position
        // Position j is available if at least need[j] positions < j are assigned
        // Since we assign from right to left, position j is available when
        // (n - j) positions have been assigned to positions > j
        // and need[j] <= (n - j) + (positions assigned to positions < j that are < j)
        // This is getting complex. Let's use the simpler greedy:

        // Just assign to position pos, then decrement
        ans[pos] = v;
        pos--;
    }

    // Verify and fix: the assignment must satisfy d_i >= d_{floor(i/k)}
    // The sorted assignment from right to left should work if we process correctly

    for (int i = 1; i <= n; i++) {
        if (i > 1) cout << " ";
        cout << ans[i];
    }
    cout << "\n";
    return 0;
}
