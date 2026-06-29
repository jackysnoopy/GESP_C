#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const int MAXN = 1005;
double x[MAXN], y[MAXN];
double dist[MAXN][MAXN];
int n, k;
double dp[MAXN][MAXN][2];
int from[MAXN][MAXN][2];
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &x[i], &y[i]);
    }
    k = 1;
    for (int i = 2; i <= n; i++) {
        if (y[i] > y[k] || (y[i] == y[k] && i < k)) {
            k = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            dist[i][j] = sqrt(dx * dx + dy * dy);
        }
    }
    int left[MAXN], right[MAXN];
    int nl = 0, nr = 0;
    for (int i = k - 1; i >= 1; i--) left[++nl] = i;
    for (int i = k + 1; i <= n; i++) right[++nr] = i;
    for (int i = 0; i <= nl; i++) {
        for (int j = 0; j <= nr; j++) {
            dp[i][j][0] = dp[i][j][1] = 1e18;
        }
    }
    dp[0][0][0] = dp[0][0][1] = 0;
    from[0][0][0] = from[0][0][1] = -1;
    for (int i = 0; i <= nl; i++) {
        for (int j = 0; j <= nr; j++) {
            if (i == 0 && j == 0) continue;
            if (i > 0) {
                double best = 1e18;
                int best_from = -1;
                if (i == 1 && j == 0) {
                    best = dist[k][left[1]];
                    best_from = 0;
                } else {
                    if (dp[i-1][j][0] + dist[left[i-1]][left[i]] < best) {
                        best = dp[i-1][j][0] + dist[left[i-1]][left[i]];
                        best_from = 0;
                    }
                    if (j > 0 && dp[i-1][j][1] + dist[right[j]][left[i]] < best) {
                        best = dp[i-1][j][1] + dist[right[j]][left[i]];
                        best_from = 1;
                    }
                }
                dp[i][j][0] = best;
                from[i][j][0] = best_from;
            }
            if (j > 0) {
                double best = 1e18;
                int best_from = -1;
                if (i == 0 && j == 1) {
                    best = dist[k][right[1]];
                    best_from = 1;
                } else {
                    if (i > 0 && dp[i][j-1][0] + dist[left[i]][right[j]] < best) {
                        best = dp[i][j-1][0] + dist[left[i]][right[j]];
                        best_from = 0;
                    }
                    if (dp[i][j-1][1] + dist[right[j-1]][right[j]] < best) {
                        best = dp[i][j-1][1] + dist[right[j-1]][right[j]];
                        best_from = 1;
                    }
                }
                dp[i][j][1] = best;
                from[i][j][1] = best_from;
            }
        }
    }
    int ans_from = 0;
    if (dp[nl][nr][1] < dp[nl][nr][0]) ans_from = 1;
    int path[MAXN];
    int pos = 0;
    int ci = nl, cj = nr, cf = ans_from;
    while (ci > 0 || cj > 0) {
        if (cf == 0) {
            path[++pos] = left[ci];
            int nf = from[ci][cj][0];
            if (nf == 0) ci--;
            else cj--;
            cf = nf;
        } else {
            path[++pos] = right[cj];
            int nf = from[ci][cj][1];
            if (nf == 0) ci--;
            else cj--;
            cf = nf;
        }
    }
    printf("%d", k);
    for (int i = pos; i >= 1; i--) {
        printf(" %d", path[i]);
    }
    printf("\n");
    return 0;
}