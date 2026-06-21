#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    // Connect k computers to hub directly (cost = d[i] each).
    // Remaining n-k computers chain through connected ones.
    // A chained computer at depth t from hub has cost t*d[i].
    // To minimize total: put n-k cheapest (by d[i]) computers on chains.
    // Wait, actually: connected computers contribute d[i] each.
    // Chained: if a computer chains through another, its cost includes the chain computer's d too.
    // Actually re-reading: "it takes no time for intermediate computers to redirect."
    // So the latency of computer i is d[i] * (depth from hub).
    // Hub-connected: depth 1, cost d[i].
    // Chained through hub-connected: depth 2, cost 2*d[i].
    // Wait no: "one bit of data to the other end in d_i milliseconds."
    // So sending from computer i through its wire takes d_i ms.
    // If i is connected to hub directly: t_i = d_i.
    // If i connects to j which connects to hub: t_i = d_i + d_j.
    // Wait: "we will assume that it takes no time for intermediate computers to redirect."
    // So only the source computer's wire matters? No...
    // Actually: the wire of computer i transfers data in d_i ms.
    // If computer i connects to hub, t_i = d_i.
    // If computer i connects to computer j (which connects to hub), 
    //   data goes i->j (d_i ms) then j->hub (d_j ms), so t_i = d_i + d_j.
    // But intermediate redirect takes no time, meaning only wire times count.
    
    // k computers connect to hub. Others chain through them.
    // A chain has structure: hub <- c1 <- c2 <- ... 
    // Latency of ck at depth m: sum of d values.
    // But actually each computer has one wire going out. 
    // Computer i's wire goes to the next computer or hub.
    // Data from i traverses i's wire, then i+1's wire, etc.
    // So latency = sum of d values along the path.
    
    // To minimize: sort by d. k smallest connect to hub (cost = their d).
    // Remaining: chain them in order of d (largest first closest to hub).
    // Wait, actually: chain = the k hub-connected computers form roots.
    // We have n-k remaining. We chain them: each chain has depth >= 1.
    // Total cost for chain of length m: d1 + (d1+d2) + ... + (d1+...+dm)
    //   = m*d1 + (m-1)*d2 + ... + 1*dm
    // To minimize: put smallest d closest to hub in each chain.
    // Overall: sort all d. k smallest go to hub. 
    // Remaining: distribute into chains. 
    // Since chains can be any length, and we want to minimize total,
    // we should put the n-k remaining computers into chains,
    // with the smallest d values closest to hub.
    
    // Actually simpler: sort d ascending. First k go to hub.
    // The rest form chains. Total = sum of d[i] for i=0..k-1 (hub) 
    //   + for chains: each remaining computer contributes its d times chain depth.
    
    // Optimal: chain the remaining in sorted order, with each chain having depth 1 from the
    // nearest hub computer. So total additional cost = sum of d[i] for remaining computers.
    // Wait, but that would just be connecting them too...
    // No, they can't all connect to hub (only k ports).
    // So they must chain. But a chain of length 2 from hub:
    // hub <- A <- B: A's latency = d[A], B's latency = d[A]+d[B].
    // hub <- C <- D: C's latency = d[C], D's latency = d[C]+d[D].
    // Total for 4 remaining: d[A]+d[A]+d[B]+d[C]+d[C]+d[D]
    //   = 2*d[A]+d[B]+2*d[C]+d[D]
    // Vs connecting all: d[A]+d[B]+d[C]+d[D].
    // So chaining costs extra. Each chain adds its head's d once more for each child.
    
    // Optimal strategy: sort d ascending. First k to hub.
    // Remaining: form chains. To minimize, pair them up optimally.
    // This is complex. Let me think of it as: total = sum(all d[i]) + extra.
    // Extra = for each non-hub computer, sum of d values between it and hub.
    // With optimal arrangement: sort remaining ascending, form chains greedily.
    // Each chain: head connects to hub. Child connects to head. etc.
    // Total cost = sum(hub d[i]) + sum(chain head d[j]) + sum(chain child d[k]) + ...
    //   = sum of d[i] at each depth level * depth.
    // With k chains (k hub ports), and n-k remaining:
    // We want to minimize: for each chain, the weighted sum.
    // Optimal: sort remaining ascending, distribute round-robin to chains.
    
    // Actually: think of it as each chain having some computers.
    // The first computer in each chain costs its d once (already counted in hub cost? No.)
    // Wait, hub-connected computers: k of them. Their cost = d[i] each.
    // Chain computers: each chain is rooted at a hub-connected computer.
    // A chain computer at depth 2 from hub: its latency = d[chain_head] + d[this].
    //   d[chain_head] is already part of chain_head's own latency.
    //   So extra cost = d[this] (for being in chain).
    // A chain computer at depth 3: latency = d[root] + d[mid] + d[this].
    //   Extra = d[mid] + d[this].
    
    // Hmm, this is getting complex. Let me just think of it differently.
    // Total = sum over all computers of (sum of d values on path to hub).
    // For hub-connected: just d[i].
    // For chain: d[i1] + d[i2] + ... + d[ik] where these are all computers between it and hub.
    
    // Let me think of each edge (computer -> parent) contributing d[computer] to 
    // every descendant's latency. So d[i] contributes to the latency of all computers
    // in its subtree.
    
    // To minimize: sort d ascending. Put the k smallest as roots (connecting to hub).
    // Then for the remaining n-k, assign them to chains.
    // Each remaining computer adds its d to its own latency and all descendants.
    // To minimize total, we want computers with small d to have many descendants,
    // and computers with large d to have few descendants.
    
    // This is essentially: we have k chains. Distribute n-k items.
    // Each chain is a path. The first item in chain is hub-connected (already counted).
    // Remaining chain items form a path.
    
    // Actually, the k hub-connected computers can each be a root.
    // The remaining n-k computers form paths extending from these roots.
    // Total cost = sum of d[i] for hub computers + 
    //   sum over each chain of (sum of chain computer d values * their depth from root).
    
    // For a chain: root(c1) - c2 - c3 - ... - cm
    // Cost from chain = d[c1]*(m-1) + d[c2]*(m-2) + ... + d[cm-1]*1
    //   Wait no. c1's d contributes to all m-1 descendants. c2's d to m-2. etc.
    //   Total chain extra = d[c1]*(m-1) + d[c2]*(m-2) + ... + d[cm-1]*1
    // To minimize: put smallest d at the top (c1), largest at bottom.
    
    // With n-k remaining computers distributed among k chains:
    // Sort remaining ascending. Round-robin distribute.
    // Actually the optimal is to distribute such that chains are as balanced as possible,
    // with smallest d values at the top of each chain.
    
    // Hmm, let me just code the greedy: sort all d. First k go to hub.
    // Remaining sorted ascending. Distribute round-robin to chains.
    // For each chain, compute extra cost.
    
    sort(d.begin(), d.end());
    long long total = 0;
    // First k: hub connected
    for (int i = 0; i < k; i++) total += d[i];
    // Remaining: n-k computers, distribute to k chains
    // Chain j has depth 1 (the hub connection). Each added computer increases depth by 1.
    // Round-robin: assign remaining[i] to chain[i % k].
    vector<int> chainDepth(k, 0); // depth of next computer in each chain
    for (int i = k; i < n; i++) {
        int chain = (i - k) % k;
        chainDepth[chain]++;
        // This computer's d contributes to its own latency (once) plus chain depth.
        // Actually: its latency = d[chain_root] + d[chain_parent] + ... + d[this]
        // The "chain_root" d is already counted in hub total.
        // Extra for this computer = sum of d values between root and this (exclusive of root).
        // But we're building greedily: each computer added to a chain has its d counted
        // (chainDepth[chain]) more times for future computers.
        // Total extra = for each chain, sum of d[chain_computer_j] * (chain_length - j - 1)
    }
    // Let me redo this more carefully.
    // For each chain, we have a sequence of computers.
    // Chain costs:
    //   - The hub-connected computer: d[hub_comp] (already in total)
    //   - Chain child 1: d[hub_comp] + d[child1] (extra: d[child1])
    //   - Chain child 2: d[hub_comp] + d[child1] + d[child2] (extra: d[child1]+d[child2])
    //   - etc.
    // Total extra for chain of length m: (m-1)*d[child1] + (m-2)*d[child2] + ... + 1*d[child_m]
    //   wait no: child1 contributes to m-1 descendants (itself plus all below). Actually:
    //   The hub computer has latency d[hub].
    //   Child 1 has latency d[hub]+d[c1]. Extra = d[c1].
    //   Child 2 has latency d[hub]+d[c1]+d[c2]. Extra = d[c1]+d[c2].
    //   Child m has extra = d[c1]+d[c2]+...+d[cm].
    //   Total extra = m*d[c1] + (m-1)*d[c2] + ... + 1*d[cm].
    // To minimize: sort chain computers ascending, put smallest first.
    
    // With round-robin: chain j gets computers k+j, k+j+k, k+j+2k, ...
    // Sort remaining ascending. Assign round-robin.
    // For each chain, the computers are already in ascending order.
    
    // Total = hub_sum + extra
    // extra for chain j: if it has m computers c1<=c2<=...<=cm:
    //   m*c1 + (m-1)*c2 + ... + 1*cm
    
    vector<vector<int>> chains(k);
    for (int i = k; i < n; i++) {
        chains[(i - k) % k].push_back(d[i]);
    }
    for (int j = 0; j < k; j++) {
        int m = chains[j].size();
        for (int t = 0; t < m; t++) {
            total += (long long)(m - t) * chains[j][t];
        }
    }
    cout << total << endl;
    return 0;
}
