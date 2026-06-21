#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int n, L;
vector<int> a;

bool check(double mid) {
    vector<double> pre(n + 1, 0);
    for (int i = 1; i <= n; i++)
        pre[i] = pre[i-1] + a[i-1] - mid;
    double min_pre = 0;
    for (int i = L; i <= n; i++) {
        min_pre = min(min_pre, pre[i - L]);
        if (pre[i] - min_pre >= 0) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> L;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    double lo = 0, hi = 2000;
    for (int iter = 0; iter < 50; iter++) {
        double mid = (lo + hi) / 2;
        if (check(mid)) lo = mid;
        else hi = mid;
    }
    
    cout << (int)(hi * 1000) << "\n";
    return 0;
}