#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, m;
vector<pair<int,int>> factories;
vector<vector<int>> typeFact;

double calcCost(double pos) {
    double total = 0;
    for (int t = 0; t < n; t++) {
        double best = 1e18;
        for (int f : typeFact[t]) {
            double d = pos - factories[f].first;
            best = min(best, d * d);
        }
        total += best;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    factories.resize(m);
    typeFact.resize(n);
    for (int i = 0; i < m; i++) {
        cin >> factories[i].first >> factories[i].second;
        typeFact[factories[i].second - 1].push_back(i);
    }
    double lo = factories[0].first, hi = factories[m - 1].first;
    for (int iter = 0; iter < 200; iter++) {
        double m1 = lo + (hi - lo) / 3;
        double m2 = hi - (hi - lo) / 3;
        if (calcCost(m1) < calcCost(m2)) hi = m2;
        else lo = m1;
    }
    double ans = (lo + hi) / 2;
    printf("%.4f\n", ans);
    return 0;
}
