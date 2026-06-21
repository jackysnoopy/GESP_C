#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int F, M, N;
    cin >> F >> M >> N;
    vector<int> fi(N), mi(N);
    for (int i = 0; i < N; i++) cin >> fi[i] >> mi[i];
    // Maximize (F + sum of selected fi) / (M + sum of selected mi)
    // Check if ratio > mid: F+Sf > mid*(M+Sm) => F - mid*M > mid*Sm - Sf
    // => sum(mid*mi - fi) < F - mid*M
    double lo = 0, hi = 1e6;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        // Check if we can achieve ratio > mid
        // Sort by (mid*mi - fi) ascending, take negative ones
        vector<pair<double,int>> val(N);
        for (int i = 0; i < N; i++) val[i] = {mid * mi[i] - fi[i], i};
        sort(val.begin(), val.end());
        double need = F - mid * M;
        double sum = 0;
        for (int i = 0; i < N; i++) {
            if (val[i].first < 0) { sum += val[i].first; }
        }
        if (-sum < need) lo = mid;
        else hi = mid;
    }
    // Greedy: take parts where fi/mi > current ratio
    double ratio = lo;
    vector<int> result;
    for (int i = 0; i < N; i++) {
        if ((double)fi[i] / mi[i] > ratio) result.push_back(i + 1);
    }
    if (result.empty()) cout << "NONE\n";
    else for (int x : result) cout << x << "\n";
    return 0;
}
