#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

// P1404: 平均数
// Find max average of contiguous subarray of length >= m, output floor(avg * 1000)
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    
    double lo = 0, hi = 1e9;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2.0;
        vector<double> b(n);
        for (int i = 0; i < n; i++) b[i] = a[i] - mid;
        
        vector<double> pre(n + 1, 0);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + b[i];
        
        double minPre = 0;
        bool ok = false;
        for (int j = m; j <= n; j++) {
            minPre = min(minPre, pre[j - m]);
            if (pre[j] >= minPre) { ok = true; break; }
        }
        if (ok) lo = mid; else hi = mid;
    }
    printf("%d\n", (int)(lo * 1000));
    return 0;
}
