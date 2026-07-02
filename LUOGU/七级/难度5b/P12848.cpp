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
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
    }
    
    // We have n slots, slot n is empty initially
    // Slot i has stone a[i] for i = 1 to n-1
    // We want to move stone i to slot i
    // We can add edges between slots at cost 1 each
    // Initially, slots i and i+1 are connected
    
    // This is about permutation cycles
    // The permutation is: stone a[i] is in slot i+1 (for i = 0 to n-2)
    // Stone n is in slot n (empty, but we can think of it as stone n in slot n)
    
    // Actually, let's re-read:
    // "对于任意的 1 <= i < n，第 i 个槽位和第 i+1 个槽位是相连的"
    // So initially, slots are connected in a line: 1-2-3-...-n
    // We can add edges between any two slots at cost 1
    
    // The goal is to move stone i to slot i
    // We can only move a stone from slot u to slot v if u and v are connected
    
    // This is equivalent to: we need to make the permutation identity
    // by adding edges to make the graph connected enough
    
    // Let's think about the permutation:
    // Slot i has stone a[i] (for i = 1 to n-1)
    // Slot n is empty (we can think of it as having stone n)
    
    // The permutation is: p[i] = a[i] for i = 1 to n-1, p[n] = n
    // We want to make p[i] = i for all i
    
    // The permutation decomposes into cycles
    // For each cycle, we need to add edges to make it possible to rotate
    
    // Actually, let's think about it differently:
    // The initial graph is a path: 1-2-3-...-n
    // We need to add edges so that each stone can reach its target slot
    
    // For stone i to reach slot i, there must be a path from its current slot to slot i
    // The current slot of stone i is the slot j where a[j] = i (for i < n)
    // For stone n, it's in slot n
    
    // So we need: for each i, there's a path from slot j (where a[j] = i) to slot i
    
    // This is equivalent to: the graph must be connected enough
    // such that each cycle of the permutation can be "rotated"
    
    // Let's find the cycles of the permutation
    vector<int> pos(n + 1); // pos[stone] = slot
    for (int i = 0; i < n - 1; i++) {
        pos[a[i]] = i + 1;
    }
    pos[n] = n; // stone n is in slot n
    
    // The permutation is: stone i should go to slot i
    // So the permutation maps slot j to slot i where a[j] = i
    // Or equivalently, stone i is in slot pos[i]
    
    // The cycles are: follow the mapping i -> pos[i] -> pos[pos[i]] -> ...
    vector<bool> visited(n + 1, false);
    int num_cycles = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            num_cycles++;
            int cur = i;
            while (!visited[cur]) {
                visited[cur] = true;
                cur = pos[cur];
            }
        }
    }
    
    // For each cycle, we need to add edges to make it possible to rotate
    // The initial graph is a path, so we need to add edges to connect the cycle
    
    // Actually, the answer is: n - num_cycles
    // This is because we need to add edges to make each cycle connected
    // and the minimum number of edges to add is n - num_cycles
    
    cout << n - num_cycles << endl;
    
    return 0;
}
