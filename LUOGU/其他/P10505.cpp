#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, k;
    while (cin >> n >> k && (n || k)) {
        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];
        double lo = 0, hi = 100;
        for (int iter = 0; iter < 50; ++iter) {
            double mid = (lo + hi) / 2;
            vector<double> c(n);
            for (int i = 0; i < n; ++i) c[i] = a[i] - mid * b[i];
            sort(c.begin(), c.end(), greater<double>());
            double sum = 0;
            for (int i = 0; i < n - k; ++i) sum += c[i];
            if (sum >= 0) lo = mid; else hi = mid;
        }
        printf("%.0f\n", lo * 100);
    }
    return 0;
}
