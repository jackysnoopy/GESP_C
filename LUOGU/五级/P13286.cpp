#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;

int main() {
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        ll E, R;
        int N;
        scanf("%lld %lld %d", &E, &R, &N);
        vector<ll> v(N);
        for (int i = 0; i < N; i++) scanf("%lld", &v[i]);
        
        // Greedy: for each activity, determine how much energy to spend
        // Key: for activity i, find the next activity j with v[j] > v[i]
        // Spend energy so that we have exactly enough to reach j (or E if no such j)
        
        // For each activity, compute the "reach": how far ahead we can see a higher-value activity
        // Energy available at activity i = min(E, R * (i - last_reset))
        // But this is complex. Use the standard greedy approach:
        
        // For each activity i, find next[i] = next activity with v[j] >= v[i]
        // The energy we can spend on i is limited by how much we need to save for next[i]
        
        // Standard approach: 
        // 1. For each activity, find the next activity with strictly greater value
        // 2. The energy we can use on activity i is:
        //    min(E, R * distance_to_next_greater) if next_greater exists
        //    E otherwise (last activity or no greater value after)
        
        vector<int> next_greater(N, N);
        {
            vector<int> stk;
            for (int i = N - 1; i >= 0; i--) {
                while (!stk.empty() && v[stk.back()] <= v[i]) stk.pop_back();
                if (!stk.empty()) next_greater[i] = stk.back();
                stk.push_back(i);
            }
        }
        
        ll energy = E;
        ll total = 0;
        for (int i = 0; i < N; i++) {
            // Energy available: energy (capped at E)
            energy = min(energy, E);
            
            // How much energy to spend?
            ll spend;
            if (next_greater[i] == N) {
                // No greater value after this, spend all
                spend = energy;
            } else {
                // Need to save enough to reach next_greater[i]
                // After spending s on activity i, we get R back, then use energy for activities i+1..next_greater[i]-1
                // The minimum energy we can have at next_greater[i] is max(0, energy - s + R * (next_greater[i] - i))
                // We need this to be >= min(E, R) (at least some energy)
                // Actually, we just need to not waste energy. Spend so that energy at next_greater is exactly E.
                ll dist = next_greater[i] - i;
                ll needed = E - dist * R; // energy we need to keep now to have E at next_greater
                // But we might not have enough to keep
                // Spend = max(0, min(energy, energy - needed))
                // But needed could be negative (we'll recover more than E before reaching)
                if (needed <= 0) {
                    spend = energy; // We'll recover to E anyway before reaching next_greater
                } else {
                    spend = max(0LL, energy - needed);
                }
                // Also cap: don't spend more than E
                spend = min(spend, energy);
            }
            
            total += spend * v[i];
            energy -= spend;
            energy += R;
            energy = min(energy, E);
        }
        
        printf("Case #%d: %lld\n", t, total);
    }
    return 0;
}
