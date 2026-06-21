#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// [C.E.L.U-03] 重构
// n servers, connect with n-1 edges. Minimize sum(d_i^2 * v_i).
// Greedy: connect nodes with largest v_i to as few others as possible (degree 1).
// Connect nodes with smallest v_i to as many others as possible.
// Optimal: the node with smallest v gets degree n-1 (star center).
// Wait, that gives sum = (n-1)^2 * v_min + sum of rest (1^2 * v_i for others).
// But maybe a different distribution is better.
// 
// We have n nodes with degrees d_1,...,d_n where sum(d_i) = 2(n-1), each d_i >= 1.
// Minimize sum(d_i^2 * v_i).
// By the rearrangement inequality, assign largest d to smallest v.
// So sort v in decreasing order, assign degrees in increasing order.
// The degree sequence: we want to assign degrees d_1 <= d_2 <= ... <= d_n to v_1 >= v_2 >= ... >= v_n.
// 
// What degree sequences are valid (graphical) for trees? sum = 2(n-1), each >= 1.
// Any such sequence is valid for a tree as long as sum = 2(n-1) and each >= 1.
// So the minimum sum(d_i^2 * v_i) is achieved by:
// Sort v descending. Assign degrees ascending to them.
// But what's the optimal degree assignment?
// 
// We want to minimize sum(d_i^2 * v_i) subject to sum(d_i) = 2(n-1), d_i >= 1.
// Lagrange: 2*d_i*v_i = lambda, so d_i = lambda/(2*v_i).
// But d_i must be integers >= 1.
// 
// Simple approach: sort v descending. Assign d = (1,1,...,1, 2(n-1)-(n-1)) = (1,1,...,1,n-1)
// where the node with smallest v gets degree n-1.
// sum = sum(v_i * 1) + v_min * (n-1)^2 - v_min * 1 = sum(v) + v_min * ((n-1)^2 - 1)
// 
// But we can also try: give the two smallest v nodes higher degrees.
// Actually, the optimal is to give one node degree n-1 (star), and all others degree 1.
// sum = sum(v_i) + v_min * ((n-1)^2 - 1).
// 
// Wait, can we do better? If v_min is not that small relative to others,
// distributing the degree might help.
// E.g., n=4, v = [10,10,1,1], target sum = 6.
// Star with center at v=1: 10+10+1+1*9 = 30.
// Two centers: degrees (1,1,2,2): 10+10+4+4 = 28. Better!
// 
// So it's not always star. We need to find the optimal degree assignment.
// 
// General approach: sort v descending. Assign d_i values.
// Each d_i >= 1, sum = 2(n-1). Minimize sum(d_i^2 * v_i).
// Since the objective is convex in d_i, we should distribute degree as evenly as possible
// among the low-v nodes.
// 
// This is a resource allocation problem. We have (n-1) extra degree units to distribute
// (each node starts with 1, total 2n, need 2n-2, so extra = n-2).
// Each extra unit at node i increases the objective by: 
// (d_i+1)^2*v_i - d_i^2*v_i = (2*d_i+1)*v_i.
// Greedy: always put the next unit where the increase is smallest.
// Since all start at d_i=1, first extra at node i costs 3*v_i.
// Use a priority queue.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    
    // Min-heap: (cost, node_index). cost = (2*d+1)*v[node]
    // We need to distribute n-2 extra degree units.
    // But we should sort v so that nodes with smaller v get more degree.
    // Use a min-heap on (2*d+1)*v.
    
    // Actually, just use a priority queue approach:
    // Start with all degrees = 1. Extra = n-2.
    // For each extra unit, add to the node where (2*d_i+1)*v_i is minimum.
    
    long long ans = 0;
    for (int i = 0; i < n; i++) ans += v[i]; // each starts with degree 1: d^2*v = 1*v = v
    
    // Priority queue: {increment, node_index}
    // increment for adding one more degree to node i with current degree d_i is (2*d_i+1)*v_i
    struct Item {
        long long cost;
        int idx;
        bool operator>(const Item& o) const { return cost > o.cost; }
    };
    
    vector<int> deg(n, 1);
    priority_queue<Item, vector<Item>, greater<Item>> pq;
    for (int i = 0; i < n; i++) {
        pq.push({3 * v[i], i});
    }
    
    int extra = n - 2;
    while (extra > 0) {
        Item top = pq.top(); pq.pop();
        int i = top.idx;
        ans += (long long)(2 * deg[i] + 1) * v[i];
        deg[i]++;
        pq.push({(long long)(2 * deg[i] + 1) * v[i], i});
        extra--;
    }
    
    cout << ans << "\n";
    return 0;
}
