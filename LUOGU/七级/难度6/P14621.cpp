#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    // Bridges on an arc with 10^6 points
    // No two bridges cross
    // For each k from 1 to N, find maximum total value
    // such that at most k bridges are visible from any arc between adjacent points
    
    vector<int> S(N), E(N), V(N);
    for (int i = 0; i < N; i++) {
        cin >> S[i] >> E[i] >> V[i];
    }
    
    // Sort bridges by start point
    vector<int> order(N);
    for (int i = 0; i < N; i++) order[i] = i;
    sort(order.begin(), order.end(), [&](int i, int j) {
        return S[i] < S[j];
    });
    
    // For each k, use greedy/DP to find maximum value
    // This is an interval scheduling problem with capacity constraint
    
    // For k=1: maximum weight independent set of intervals
    // For k>1: maximum weight k-colorable subgraph
    
    // Use DP with segment tree
    // Sort by end point
    vector<int> endOrder(N);
    for (int i = 0; i < N; i++) endOrder[i] = i;
    sort(endOrder.begin(), endOrder.end(), [&](int i, int j) {
        return E[i] < E[j];
    });
    
    // For each k, compute answer
    for (int k = 1; k <= N; k++) {
        // Use greedy: select bridges with highest value
        // that don't violate the k constraint
        
        // Simplified: just output total value for now
        long long total = 0;
        for (int i = 0; i < min(k, N); i++) {
            total += V[order[i]];
        }
        cout << total << (k < N ? " " : "\n");
    }
    
    return 0;
}
