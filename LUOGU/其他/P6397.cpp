#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    double k;
    int n;
    cin >> k >> n;
    vector<double> d(n);
    for (int i = 0; i < n; i++) cin >> d[i];
    double lo = 0, hi = 1e9;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        double cur = 0;
        bool ok = true;
        for (int i = 1; i < n; i++) {
            if (d[i] - d[i-1] > 2 * mid + 2 * k) {
                ok = false;
                break;
            }
            double need = (d[i] - d[i-1] - 2 * k) / 2.0;
            if (need > mid) need = mid;
            cur = max(cur, need);
        }
        if (ok && cur <= mid) hi = mid;
        else lo = mid;
    }
    printf("%.3f\n", hi);
    return 0;
}
