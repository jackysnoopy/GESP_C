#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int need[4];
double dp[1 << 4][16][16][16][16];

double solve(int mask, int c0, int c1, int c2, int c3) {
    if (mask == 15) return 0;
    double &res = dp[mask][c0][c1][c2][c3];
    if (res >= -0.5) return res;
    int total = 54;
    int rem = total - (13 - c0) - (13 - c1) - (13 - c2) - (13 - c3);
    if (rem == 0) return res = 1e18;
    res = 1;
    int cnt[4] = {c0, c1, c2, c3};
    for (int i = 0; i < 4; ++i) {
        if (cnt[i] > 0) {
            double p = (double)cnt[i] / total;
            int nmask = mask;
            if (cnt[i] <= need[i]) nmask |= (1 << i);
            res += p * solve(nmask, cnt[i] - 1, cnt[(i+1)%4], cnt[(i+2)%4], cnt[(i+3)%4]);
        }
    }
    res += (double)(total - cnt[0] - cnt[1] - cnt[2] - cnt[3]) / total * 1;
    return res;
}

int main() {
    int cs = 0;
    while (scanf("%d%d%d%d", &need[0], &need[1], &need[2], &need[3]) == 4) {
        if (need[0] + need[1] + need[2] + need[3] == 0) break;
        memset(dp, -1, sizeof(dp));
        double ans = solve(0, 13, 13, 13, 13);
        printf("Case %d: ", ++cs);
        if (ans > 1e17) printf("-1.000\n");
        else printf("%.3f\n", ans);
    }
    return 0;
}
