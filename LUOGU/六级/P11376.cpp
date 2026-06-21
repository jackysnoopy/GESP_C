#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    long long x;
    cin >> n >> m >> x;

    vector<pair<long long, int>> stations(n);
    for (int i = 0; i < n; i++) {
        cin >> stations[i].first >> stations[i].second;
    }

    vector<long long> d(m);
    long long sum_b = 0;
    for (int i = 0; i < m; i++) {
        long long a, b;
        cin >> a >> b;
        d[i] = a - b;
        sum_b += b;
    }

    // 展开站点容量
    vector<long long> p_vals;
    for (auto &st : stations) {
        for (int k = 0; k < st.second; k++) {
            p_vals.push_back(st.first);
        }
    }

    sort(d.begin(), d.end());
    sort(p_vals.begin(), p_vals.end());

    int ld = 0, rd = m - 1;
    int lp = 0, rp = (int)p_vals.size() - 1;
    long long sum_dp = 0;

    while (ld <= rd) {
        if (llabs(d[ld]) > llabs(d[rd]) || d[ld] + d[rd] < 0) {
            sum_dp += d[ld] * p_vals[rp];
            ld++;
            rp--;
        } else {
            sum_dp += d[rd] * p_vals[lp];
            rd--;
            lp++;
        }
    }

    long long ans = 2 * x * sum_b + 2 * sum_dp;
    cout << ans << "\n";

    return 0;
}
