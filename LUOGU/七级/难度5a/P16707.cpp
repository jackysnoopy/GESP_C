#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<long long> x(n), c(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    // worst(p) = sum of sorted(|x[i]-p|) * sorted(c) (both ascending)
    // by rearrangement inequality
    // This is convex in p, use ternary search
    auto worst = [&](long long p) -> long long {
        vector<long long> dist(n);
        for (int i = 0; i < n; i++) dist[i] = abs(x[i] - p);
        sort(dist.begin(), dist.end());
        long long res = 0;
        for (int i = 0; i < n; i++) res += dist[i] * c[i];
        return res;
    };
    long long lo = x[0], hi = x[n-1];
    while (hi - lo > 2) {
        long long m1 = lo + (hi - lo) / 3;
        long long m2 = hi - (hi - lo) / 3;
        if (worst(m1) < worst(m2)) hi = m2;
        else lo = m1;
    }
    long long best = lo;
    long long best_val = worst(lo);
    for (long long p = lo; p <= hi; p++) {
        long long v = worst(p);
        if (v < best_val) { best_val = v; best = p; }
    }
    cout << best << "\n";
    return 0;
}
