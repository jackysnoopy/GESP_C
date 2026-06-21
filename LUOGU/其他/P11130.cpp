#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        long long n, m; cin >> n >> m;
        if (n == m) { cout << 0 << "\n"; continue; }
        if (m % n != 0) { cout << -1 << "\n"; continue; }
        long long ratio = m / n;
        // Check: every prime factor of ratio must divide n
        long long temp = ratio;
        vector<pair<long long,int>> factors;
        for (long long p = 2; p * p <= temp; p++) {
            if (temp % p == 0) {
                int cnt = 0;
                while (temp % p == 0) { cnt++; temp /= p; }
                factors.push_back({p, cnt});
            }
        }
        if (temp > 1) factors.push_back({temp, 1});
        
        bool ok = true;
        int ans = 0;
        for (auto& f : factors) {
            long long p = f.first;
            int need = f.second;
            // Count exponent of p in n
            long long nn = n;
            int have = 0;
            while (nn % p == 0) { have++; nn /= p; }
            if (have == 0) { ok = false; break; }
            // Need to go from have to have + need
            // At each step, exponent can at most double
            int steps = 0;
            long long cur = have;
            while (cur < have + need) {
                cur *= 2;
                steps++;
            }
            ans = max(ans, steps);
        }
        if (!ok) cout << -1 << "\n";
        else cout << ans << "\n";
    }
    return 0;
}
