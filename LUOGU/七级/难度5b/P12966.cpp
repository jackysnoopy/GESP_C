#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long n, m;
    cin >> n >> m;
    
    vector<long long> v(n), mass(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i] >> mass[i];
    }
    
    // Special property: for any two chunks, one's mass divides the other
    // This means all masses are of the form d, 2d, 4d, ... for some base d
    
    // Group chunks by mass
    vector<pair<long long, long long>> chunks; // (mass, value)
    for (int i = 0; i < n; i++) {
        chunks.push_back({mass[i], v[i]});
    }
    
    // Sort by mass
    sort(chunks.begin(), chunks.end());
    
    // Since masses have divisibility property, we can use a greedy approach
    // Process from smallest to largest mass
    
    // For each mass level, we can choose to take some chunks
    // The constraint is that total mass <= m
    
    // This is a knapsack problem with special structure
    // Let's use dynamic programming
    
    // Group by mass
    vector<vector<long long>> groups; // groups[i] = values of chunks with mass groups[i][0]
    vector<long long> group_mass;
    
    for (int i = 0; i < n; i++) {
        if (group_mass.empty() || chunks[i].first != group_mass.back()) {
            group_mass.push_back(chunks[i].first);
            groups.push_back({});
        }
        groups.back().push_back(chunks[i].second);
    }
    
    // Sort values in each group in descending order
    for (auto& g : groups) {
        sort(g.rbegin(), g.rend());
    }
    
    // DP: dp[j] = maximum value with total mass exactly j
    // But m can be up to 10^12, so we can't use array
    
    // Let's use a greedy approach instead
    // Since masses have divisibility property, we can process from largest to smallest
    
    long long ans = 0;
    long long remaining = m;
    
    // Process from largest mass to smallest
    for (int i = group_mass.size() - 1; i >= 0; i--) {
        long long mass_val = group_mass[i];
        long long max_count = remaining / mass_val;
        
        // Take the best values from this group
        long long taken = 0;
        for (long long val : groups[i]) {
            if (taken >= max_count) break;
            ans += val;
            taken++;
        }
        
        remaining -= taken * mass_val;
    }
    
    cout << ans << endl;
    
    return 0;
}
