#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<int> p(m), c(m);
    vector<int> cnt(n + 1, 0);
    for (int i = 0; i < m; i++) { cin >> p[i]; cnt[p[i]]++; }
    for (int i = 0; i < m; i++) cin >> c[i];
    vector<long long> other_costs;
    for (int i = 0; i < m; i++) {
        if (p[i] != 1) other_costs.push_back(c[i]);
    }
    sort(other_costs.begin(), other_costs.end());
    long long ans = 1e18;
    int c1 = cnt[1];
    for (int k = c1; k <= c1 + (int)other_costs.size(); k++) {
        long long cur = 0;
        int need = k - c1;
        if (need > (int)other_costs.size()) continue;
        for (int i = 0; i < need; i++) cur += other_costs[i];
        bool ok = true;
        for (int j = 2; j <= n; j++) {
            if (cnt[j] >= k) {
                int extra = cnt[j] - k + 1;
                vector<long long> jc;
                for (int i = 0; i < m; i++)
                    if (p[i] == j) jc.push_back(c[i]);
                sort(jc.begin(), jc.end());
                if (extra > (int)jc.size()) { ok = false; break; }
                for (int i = 0; i < extra; i++) cur += jc[i];
            }
        }
        if (ok) ans = min(ans, cur);
    }
    cout << ans << "\n";
    return 0;
}
