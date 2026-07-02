#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Point {
    double x, y;
};

int n;
Point pts[15];
double dist[15][15];
double memo[15][1 << 15];

double dp(int cur, int mask) {
    if (mask == (1 << n) - 1) return dist[cur][0];

    double& ret = memo[cur][mask];
    if (ret >= 0) return ret;

    ret = 1e18;
    for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) continue;
        ret = min(ret, dist[cur][i] + dp(i, mask | (1 << i)));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseno = 0;
    while (cin >> n && n != 0) {
        n += 1;
        cin >> pts[0].x >> pts[0].y;
        for (int i = 1; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double dx = pts[i].x - pts[j].x;
                double dy = pts[i].y - pts[j].y;
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < (1 << n); j++)
                memo[i][j] = -1;

        double ans = dp(0, 1);

        if (caseno > 0) cout << "\n";
        cout << "Network " << ++caseno << "\n";
        cout << "Number of lights required is " << (int)(ans + 0.5) << "\n";
    }

    return 0;
}
