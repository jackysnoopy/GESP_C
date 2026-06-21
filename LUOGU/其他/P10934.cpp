#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> planted(n + 2, 0);
    vector<pair<int,pair<int,int>>> constraints;
    for (int i = 0; i < m; i++) {
        int b, e, t; cin >> b >> e >> t;
        constraints.push_back({e, {b, t}});
    }
    sort(constraints.begin(), constraints.end());
    vector<int> prefix(n + 2, 0);
    int total = 0;
    for (auto& c : constraints) {
        int e = c.first, b = c.second.first, t = c.second.second;
        int cnt = prefix[e] - prefix[b - 1];
        if (cnt >= t) continue;
        int need = t - cnt;
        for (int pos = e; pos >= b && need > 0; pos--) {
            if (planted[pos] == 0) {
                planted[pos] = 1;
                total++;
                need--;
                for (int j = pos; j <= n; j++) prefix[j]++;
            }
        }
    }
    cout << total << "\n";
    return 0;
}
