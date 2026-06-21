#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> dir, dist;
    for (int i = 0; i < n; i++) {
        string cmd; int x;
        cin >> cmd >> x;
        if (cmd == "forward" || cmd == "backward") {
            dir.push_back(cmd == "forward" ? 1 : -1);
            dist.push_back(x);
        }
    }
    int m = dir.size();
    double best = 0;
    for (int mask = 0; mask < (1<<m); mask++) {
        double dx = 0, dy = 0;
        int angle = 0;
        for (int i = 0; i < m; i++) {
            double rad = angle * M_PI / 180.0;
            int d = dir[i];
            if (mask & (1<<i)) d = -d;
            dx += d * dist[i] * cos(rad);
            dy += d * dist[i] * sin(rad);
            angle += 90; // next command faces right
        }
        best = max(best, dx*dx + dy*dy);
    }
    // Also try rotations of the whole thing
    // Actually we need to consider all 4 orientations
    for (int rot = 0; rot < 4; rot++) {
        for (int mask = 0; mask < (1<<m); mask++) {
            double dx = 0, dy = 0;
            int angle = rot * 90;
            for (int i = 0; i < m; i++) {
                double rad = angle * M_PI / 180.0;
                int d = dir[i];
                if (mask & (1<<i)) d = -d;
                dx += d * dist[i] * cos(rad);
                dy += d * dist[i] * sin(rad);
                angle += 90;
            }
            best = max(best, dx*dx + dy*dy);
        }
    }
    cout << fixed << setprecision(6) << sqrt(best) << "\n";
    return 0;
}
