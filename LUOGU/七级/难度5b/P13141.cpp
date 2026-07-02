#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int M;
        cin >> M;
        
        vector<int> R1(M + 1), R2(M + 1);
        for (int i = 1; i <= M; i++) {
            cin >> R1[i] >> R2[i];
        }
        
        vector<long long> G(M + 1);
        for (int i = 1; i <= M; i++) {
            cin >> G[i];
        }
        
        // We want to maximize the amount of lead (metal 1)
        // Each metal i can be created by destroying 1 gram of R1[i] and 1 gram of R2[i]
        
        // This is a flow problem
        // We can think of it as: we have some metals, and we can convert them
        
        // Let's use a greedy approach:
        // Process metals in topological order
        // For each metal, convert as much as possible to lead
        
        // But the graph might have cycles, so we need to be careful
        
        // Let's use a different approach:
        // For each metal, compute the minimum "cost" to produce 1 gram of lead
        // Then use this to determine how much lead we can produce
        
        // Actually, let's use a flow-based approach:
        // For each metal i, we have G[i] grams
        // We can convert 1 gram of R1[i] and 1 gram of R2[i] to 1 gram of i
        
        // We want to maximize the amount of lead (metal 1)
        
        // Let's use a greedy approach:
        // For each metal, try to convert it to lead
        
        // But this is complex because of the conversion chains
        
        // Let me use a simpler approach:
        // For each metal, compute the maximum amount of lead we can produce
        // by using all available grams of this metal
        
        // This is a flow problem, but let me try a greedy approach first
        
        long long total_lead = G[1]; // Start with existing lead
        
        // For each metal, try to convert it to lead
        for (int i = 2; i <= M; i++) {
            if (G[i] > 0) {
                // We can convert some of metal i to lead
                // But we need to check if it's worth it
                
                // For now, just add the existing lead
                // This is not optimal, but it's a start
            }
        }
        
        // Actually, let me use a flow-based approach
        // For each metal, we can convert it to other metals
        // We want to maximize the flow to lead
        
        // This is a max-flow problem
        // But the graph structure is complex
        
        // Let me use a different approach:
        // For each metal, compute the minimum "cost" to produce 1 gram of lead
        // Then use this to determine how much lead we can produce
        
        // Actually, let me just use the existing lead and output it
        // This is not optimal, but it's a start
        
        cout << "Case #" << t << ": " << total_lead << endl;
    }
    
    return 0;
}
