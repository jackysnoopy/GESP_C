#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;
int a[605];
int p[605][605];
bool done[605];
bool disabled[605];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> a[i];
    for (int i = 0; i < m; i++)
        for (int j = 1; j <= n; j++)
            cin >> p[i][j];
    
    memset(done, 0, sizeof(done));
    memset(disabled, 0, sizeof(disabled));
    
    vector<int> order;
    int experiment_count = 0;
    int ray_idx = 0;
    
    // We need to produce n-m experiments
    // Strategy: for each step, pick the experiment with smallest index
    // that is not done and not disabled, considering future ray effects
    
    // Greedy: try to do experiments from smallest index
    // After doing experiment_count experiments, ray ray_idx fires
    // and disables the most vulnerable unfinished experiment
    
    // Process step by step
    for (int step = 0; step < n - m; step++) {
        // Find the best experiment to do next
        // We want to preserve small-index experiments
        // Pick the largest-index experiment that is available
        // (to save small-index ones for later when they might be disabled)
        
        // Actually, we should pick the experiment that, if we don't do it now,
        // might get disabled by a future ray.
        
        // Simpler greedy: always do the experiment with largest index
        // that won't cause a more important one to be disabled
        
        int chosen = -1;
        
        // Try experiments from largest to smallest index
        for (int i = n; i >= 1; i--) {
            if (done[i] || disabled[i]) continue;
            
            chosen = i;
            break;
        }
        
        if (chosen == -1) break;
        
        order.push_back(chosen);
        done[chosen] = true;
        experiment_count++;
        
        // Check if a ray fires after this experiment
        while (ray_idx < m && a[ray_idx] == experiment_count) {
            // Ray fires: disable the most vulnerable unfinished experiment
            for (int j = 1; j <= n; j++) {
                int exp = p[ray_idx][j];
                if (!done[exp] && !disabled[exp]) {
                    disabled[exp] = true;
                    break;
                }
            }
            ray_idx++;
        }
    }
    
    for (int i = 0; i < (int)order.size(); i++) {
        if (i > 0) cout << " ";
        cout << order[i];
    }
    cout << "\n";
    
    return 0;
}
