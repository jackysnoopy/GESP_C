#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
struct Order { int t, g, m; };
vector<Order> orders;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    orders.resize(n);
    for (int i = 0; i < n; i++) cin >> orders[i].t >> orders[i].g >> orders[i].m;
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> sel;
        for (int i = 0; i < n; i++) if (mask & (1 << i)) sel.push_back(i);
        sort(sel.begin(), sel.end(), [](int a, int b) { return orders[a].t < orders[b].t; });
        long long prod = 1, goods = 0;
        int prev_t = 0, income = 0;
        bool ok = true;
        for (int idx : sel) {
            int t = orders[idx].t, g = orders[idx].g;
            int dt = t - prev_t;
            long long need = g - goods;
            if (need <= 0) {
                goods -= g;
                income += orders[idx].m;
                prev_t = t;
                continue;
            }
            int bestQ = 0;
            long long bestG = 0;
            for (int q = 0; q <= dt; q++) {
                long long produced = (long long)(dt - q) * (prod + q);
                if (produced >= need && (bestQ == 0 || q < bestQ)) {
                    bestQ = q;
                    bestG = produced;
                }
            }
            if (bestQ == 0 && need > 0) { ok = false; break; }
            prod += bestQ;
            goods += bestG;
            goods -= g;
            income += orders[idx].m;
            prev_t = t;
        }
        if (ok) ans = max(ans, income);
    }
    cout << ans << "\n";
    return 0;
}
