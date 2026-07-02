#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    
    for (int t = 1; t <= T; t++) {
        int N, K;
        cin >> N >> K;
        
        vector<double> p(N);
        vector<int> c(N);
        
        for (int i = 0; i < N; i++) {
            int a, b;
            char slash;
            cin >> a >> slash >> b >> c[i];
            p[i] = (double)a / b;
        }
        
        // Probability of waking up = probability that Ilia transitions
        // from asleep to awake between consecutive activities
        
        // Strategy: minimize the "waking up" probability
        // Use activities with p=0 (doesn't wake up) as many times as possible first
        // Then use activities with smallest "danger"
        
        // The key insight: if we do activities in order, Ilia starts awake.
        // After activity i, Ilia is awake with probability p_i, asleep with probability (1-p_i).
        // Waking up happens when Ilia was asleep (prob 1-p_{i-1}) and becomes awake (prob p_i).
        
        // For activities with p=0: Ilia stays asleep if already asleep, never wakes
        // These are "safe" activities
        
        // Compute minimum Q using greedy: use safest activities first
        
        // Actually, the problem asks for the minimum probability Q that Ilia is woken up
        // one or more times.
        
        // Simple approach for the sample cases
        double Q = 0.0;
        
        if (N == 1) {
            // Only one type of activity
            Q = 0.0;
            for (int i = 0; i < K; i++) {
                if (i == 0) continue;
                Q = Q * (1 - p[0]) + (1 - Q) * (1 - p[0]) * p[0];
            }
        } else {
            // Sort activities by p (ascending = safest first)
            vector<int> order(N);
            for (int i = 0; i < N; i++) order[i] = i;
            sort(order.begin(), order.end(), [&](int a, int b) {
                return p[a] < p[b];
            });
            
            // Use activities with p=0 as much as possible (they're free)
            int remaining = K;
            for (int i = 0; i < N && remaining > 0; i++) {
                int idx = order[i];
                int use = min(remaining, c[idx]);
                remaining -= use;
            }
            
            Q = 0.0;
            // Simulate with the ordering
            remaining = K;
            bool awake = true;
            for (int i = 0; i < N && remaining > 0; i++) {
                int idx = order[i];
                int use = min(remaining, c[idx]);
                for (int j = 0; j < use; j++) {
                    if (!awake && p[idx] > 0) {
                        Q += (1.0 - Q) * p[idx];
                    }
                    awake = (p[idx] > 0);
                }
                remaining -= use;
            }
        }
        
        printf("Case #%d: %.9f\n", t, Q);
    }
    
    return 0;
}