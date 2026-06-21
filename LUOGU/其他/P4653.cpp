#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<double> A(n), B(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i] >> B[i];
    }
    double lo = 0, hi = 1e10;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2;
        vector<double> vals(n);
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            double v = max(A[i] - mid, 0.0) + max(B[i] - mid, 0.0);
            vals[i] = v;
            if (v > 0) cnt++;
        }
        sort(vals.rbegin(), vals.rend());
        double sum = 0;
        for (int i = 0; i < cnt && i < n; i++) {
            sum += vals[i];
        }
        if (sum >= mid) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    printf("%.4f\n", lo);
    return 0;
}
