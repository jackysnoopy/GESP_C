#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<int> vol(n), mass(n);
    for (int i = 0; i < n; i++) {
        cin >> vol[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> mass[i];
    }
    
    // Create sorted order based on volume
    vector<int> idx(n);
    for (int i = 0; i < n; i++) {
        idx[i] = i;
    }
    sort(idx.begin(), idx.end(), [&](int a, int b) {
        return vol[a] < vol[b];
    });
    
    // Find cycles in the permutation
    vector<bool> visited(n, false);
    long long ans = 0;
    int global_min_mass = *min_element(mass.begin(), mass.end());
    
    for (int i = 0; i < n; i++) {
        if (visited[i] || idx[i] == i) continue;
        
        // Find cycle
        vector<int> cycle;
        int j = i;
        while (!visited[j]) {
            visited[j] = true;
            cycle.push_back(j);
            j = idx[j];
        }
        
        // Calculate cost for this cycle
        long long cycle_sum = 0;
        int cycle_min_mass = mass[cycle[0]];
        for (int x : cycle) {
            cycle_sum += mass[x];
            cycle_min_mass = min(cycle_min_mass, mass[x]);
        }
        
        // Two strategies:
        // 1. Use cycle minimum as temporary
        long long cost1 = cycle_sum + (long long)(cycle.size() - 2) * cycle_min_mass;
        
        // 2. Use global minimum as temporary
        long long cost2 = cycle_sum + cycle_min_mass + (long long)(cycle.size() + 1) * global_min_mass;
        
        ans += min(cost1, cost2);
    }
    
    cout << ans << "\n";
    return 0;
}
