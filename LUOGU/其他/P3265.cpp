#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<pair<int, vector<double>>> equip(n);
    for (int i = 0; i < n; ++i) {
        equip[i].second.resize(m);
        for (int j = 0; j < m; ++j) cin >> equip[i].second[j];
    }
    for (int i = 0; i < n; ++i) cin >> equip[i].first;
    sort(equip.begin(), equip.end());
    vector<vector<double>> basis;
    double total = 0;
    int cnt = 0;
    const double eps = 1e-7;
    for (auto& e : equip) {
        auto v = e.second;
        for (auto& b : basis) {
            int pivot = -1;
            for (int j = 0; j < m; ++j)
                if (fabs(b[j]) > eps) { pivot = j; break; }
            if (pivot < 0) continue;
            if (fabs(v[pivot]) < eps) continue;
            double f = v[pivot] / b[pivot];
            for (int j = 0; j < m; ++j) v[j] -= f * b[j];
        }
        bool nonzero = false;
        for (int j = 0; j < m; ++j)
            if (fabs(v[j]) > eps) { nonzero = true; break; }
        if (nonzero) {
            basis.push_back(v);
            total += e.first;
            cnt++;
        }
    }
    cout << cnt << " " << (long long)(total + 0.5) << '\n';
    return 0;
}
