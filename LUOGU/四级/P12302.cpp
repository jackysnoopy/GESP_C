#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<long long> b(n), e(n);
    for (int i = 0; i < n; i++) cin >> b[i] >> e[i];
    
    // First activity must start after time 0 (we sleep at time 0)
    if (b[0] == 0) {
        cout << "impossible" << endl;
        return 0;
    }
    
    vector<pair<long long, long long>> sleeps;
    
    // First sleep at time 0, duration k = b[0] (maximize awake period)
    long long s = 0;
    long long k = b[0];
    sleeps.push_back({s, s + k});
    
    // Find first activity not covered by current awake period [s+k, s+3k]
    int idx = 0;
    while (idx < n && e[idx] <= s + 3 * k) {
        idx++;
    }
    
    // Process remaining activities
    while (idx < n) {
        long long func_start = s + 2 * k;
        long long must_sleep = s + 3 * k;
        long long last_end = (idx > 0) ? e[idx - 1] : 0;
        
        // Sleep time t: must be in function phase and after last activity
        long long t_min = max(func_start, last_end);
        // Feasibility: 2t <= 3*b[idx] - e[idx]
        long long t_feas = (3 * b[idx] - e[idx]) / 2;
        long long t = min(must_sleep, t_feas);
        if (t < t_min) t = t_min;
        
        if (t > must_sleep) {
            cout << "impossible" << endl;
            return 0;
        }
        
        // Sleep duration kp: must cover activity idx
        long long kp_lo = max(1LL, (e[idx] - t + 2) / 3);
        long long kp_hi = b[idx] - t;
        
        if (kp_lo > kp_hi) {
            cout << "impossible" << endl;
            return 0;
        }
        
        // Greedily cover as many activities as possible
        long long kp = kp_lo;
        int new_idx = idx;
        for (int j = idx; j < n; j++) {
            long long need = (e[j] - t + 2) / 3;
            if (need <= kp_hi) {
                new_idx = j + 1;
                kp = max(kp, need);
            } else {
                break;
            }
        }
        
        sleeps.push_back({t, t + kp});
        s = t;
        k = kp;
        idx = new_idx;
    }
    
    cout << sleeps.size() << endl;
    for (auto& p : sleeps) {
        cout << p.first << " " << p.second << endl;
    }
    
    return 0;
}
