#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main() {
    int n; long long k;
    scanf("%d %lld", &n, &k);
    vector<long long> a(n);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a.begin(), a.end());
    long long f1 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] <= 1) f1 += (2 - a[i]);
    }
    if (f1 > k) { printf("0\n"); return 0; }
    long long lo = 0, hi = 2000000000LL;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        long long need = 0;
        bool ok = true;
        for (int i = 0; i < n; i++) {
            if (a[i] <= mid) need += (mid + 1 - a[i]);
            if (need > mid * k) { ok = false; break; }
        }
        if (ok) lo = mid;
        else hi = mid - 1;
    }
    printf("%lld\n", lo);
    return 0;
}
