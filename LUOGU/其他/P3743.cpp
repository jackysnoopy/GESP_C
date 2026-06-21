#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p;
    cin >> n >> p;
    vector<int> a(n), b(n);
    long long sumA = 0;
    for (int i = 0; i < n; i++) { cin >> a[i] >> b[i]; sumA += a[i]; }
    if (sumA <= p) { cout << -1 << "\n"; return 0; }
    // Binary search on time
    double lo = 0, hi = 1e15;
    for (int iter = 0; iter < 200; iter++) {
        double mid = (lo + hi) / 2;
        double totalNeed = 0;
        for (int i = 0; i < n; i++) {
            double energy = b[i] - mid * a[i];
            if (energy < 0) totalNeed -= energy;
        }
        if (totalNeed <= mid * p) lo = mid;
        else hi = mid;
    }
    cout << fixed << setprecision(10) << lo << "\n";
    return 0;
}
