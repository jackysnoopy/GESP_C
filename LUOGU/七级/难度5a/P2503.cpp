#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n);
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    
    double avg = (double)sum / m;
    
    // Simulated annealing
    vector<int> group(n);
    for (int i = 0; i < n; i++) {
        group[i] = i % m;
    }
    
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    uniform_int_distribution<> dis_idx(0, n - 1);
    
    double best_cost = 1e18;
    vector<int> best_group = group;
    
    // Calculate initial cost
    vector<long long> group_sum(m, 0);
    for (int i = 0; i < n; i++) {
        group_sum[group[i]] += a[i];
    }
    
    double temp = 1000.0;
    double cooling = 0.99999;
    
    for (int iter = 0; iter < 1000000; iter++) {
        // Random swap
        int i = dis_idx(gen);
        int j = dis_idx(gen);
        if (group[i] == group[j]) continue;
        
        int gi = group[i], gj = group[j];
        
        // Calculate cost change
        double old_cost = 0;
        for (int k = 0; k < m; k++) {
            double diff = group_sum[k] - avg;
            old_cost += diff * diff;
        }
        
        // Swap
        group_sum[gi] -= a[i];
        group_sum[gj] -= a[j];
        group_sum[gi] += a[j];
        group_sum[gj] += a[i];
        swap(group[i], group[j]);
        
        double new_cost = 0;
        for (int k = 0; k < m; k++) {
            double diff = group_sum[k] - avg;
            new_cost += diff * diff;
        }
        
        double delta = new_cost - old_cost;
        
        if (delta < 0 || dis(gen) < exp(-delta / temp)) {
            if (new_cost < best_cost) {
                best_cost = new_cost;
                best_group = group;
            }
        } else {
            // Revert
            group_sum[gi] -= a[j];
            group_sum[gj] -= a[i];
            group_sum[gi] += a[i];
            group_sum[gj] += a[j];
            swap(group[i], group[j]);
        }
        
        temp *= cooling;
    }
    
    double ans = sqrt(best_cost / m);
    cout << fixed << setprecision(2) << ans << "\n";
    return 0;
}
