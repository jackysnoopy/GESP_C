#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // dp_val[i] = max product for a[0..i-1] mod MOD
    // dp_log[i] = log of the max product for comparison
    vector<ll> dp_val(n + 1, 0);
    vector<double> dp_log(n + 1, -1e18);
    dp_val[0] = 1;
    dp_log[0] = 0.0;
    
    vector<ll> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + a[i];
    
    for (int i = 1; i <= n; i++) {
        // Try all possible last group sizes (1, 2, or 3 elements)
        // Size 1: group [a[i-1]]
        {
            ll grp = a[i - 1];
            double log_val = dp_log[i - 1] + log((double)grp);
            ll val = dp_val[i - 1] * (grp % MOD) % MOD;
            if (log_val > dp_log[i] + 1e-12 || (fabs(log_val - dp_log[i]) < 1e-12 && val > dp_val[i])) {
                dp_log[i] = log_val;
                dp_val[i] = val;
            }
        }
        // Size 2: group [a[i-2], a[i-1]]
        if (i >= 2) {
            ll grp = a[i - 2] + a[i - 1];
            double log_val = dp_log[i - 2] + log((double)grp);
            ll val = dp_val[i - 2] * (grp % MOD) % MOD;
            if (log_val > dp_log[i] + 1e-12 || (fabs(log_val - dp_log[i]) < 1e-12 && val > dp_val[i])) {
                dp_log[i] = log_val;
                dp_val[i] = val;
            }
        }
        // Size 3: group [a[i-3], a[i-2], a[i-1]]
        if (i >= 3) {
            ll grp = a[i - 3] + a[i - 2] + a[i - 1];
            double log_val = dp_log[i - 3] + log((double)grp);
            ll val = dp_val[i - 3] * (grp % MOD) % MOD;
            if (log_val > dp_log[i] + 1e-12 || (fabs(log_val - dp_log[i]) < 1e-12 && val > dp_val[i])) {
                dp_log[i] = log_val;
                dp_val[i] = val;
            }
        }
    }
    
    cout << dp_val[n] << endl;
    return 0;
}
