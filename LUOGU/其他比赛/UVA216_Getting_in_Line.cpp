#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Point {
    int x, y;
};

int n;
Point pts[10];
double dist[10][10];
int order[10];
int bestOrder[10];
double bestDist;

void solve(int idx, bool used[], double curDist) {
    if (idx == n) {
        if (curDist < bestDist) {
            bestDist = curDist;
            for (int i = 0; i < n; i++) bestOrder[i] = order[i];
        }
        return;
    }

    if (curDist >= bestDist) return;

    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = true;
        order[idx] = i;
        double add = (idx == 0) ? 0 : dist[order[idx - 1]][i];
        solve(idx + 1, used, curDist + add);
        used[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int caseno = 0;
    while (cin >> n && n != 0) {
        for (int i = 0; i < n; i++) {
            cin >> pts[i].x >> pts[i].y;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dx = pts[i].x - pts[j].x;
                double dy = pts[i].y - pts[j].y;
                dist[i][j] = dist[j][i] = sqrt(dx * dx + dy * dy);
            }
        }

        bestDist = 1e18;
        bool used[10] = {};
        solve(0, used, 0);

        cout << "Network #" << ++caseno << "\n";
        for (int i = 1; i < n; i++) {
            cout << "Cable requirement to connect (" << pts[bestOrder[i - 1]].x
                 << "," << pts[bestOrder[i - 1]].y << ") to ("
                 << pts[bestOrder[i]].x << "," << pts[bestOrder[i]].y
                 << ") is " << fixed << setprecision(2)
                 << dist[bestOrder[i - 1]][bestOrder[i]] + 16.0 << " feet.\n";
        }
        cout << "Number of feet of cable required is " << fixed << setprecision(2)
             << bestDist + 16.0 * (n - 1) << ".\n\n";
    }

    return 0;
}
