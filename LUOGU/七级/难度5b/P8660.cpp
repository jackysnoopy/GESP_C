#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int MAXN = 10005;
struct Interval {
    int a, b;
    bool operator<(const Interval& other) const {
        return a < other.a;
    }
} intervals[MAXN];
int n;
bool check(double d) {
    double pos = 0.0;
    int idx = 0;
    while (pos < 10000.0) {
        double best = pos;
        while (idx < n && intervals[idx].a - d <= pos) {
            best = max(best, (double)intervals[idx].b + d);
            idx++;
        }
        if (best <= pos) return false;
        pos = best;
    }
    return true;
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &intervals[i].a, &intervals[i].b);
    }
    sort(intervals, intervals + n);
    double lo = 0.0, hi = 10000.0;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (lo + hi) / 2.0;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid;
        }
    }
    double ans = (lo + hi) / 2.0;
    if (fabs(ans - round(ans)) < 0.05) {
        printf("%.0f\n", round(ans));
    } else {
        printf("%.1f\n", ans);
    }
    return 0;
}